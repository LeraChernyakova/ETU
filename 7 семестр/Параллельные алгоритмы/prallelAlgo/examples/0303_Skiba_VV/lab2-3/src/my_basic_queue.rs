use std::{cell::RefCell, mem};
use crate::custom_sync_primitieves::*;
use std::sync::Arc;
use std::sync::atomic::Ordering;
use crate::{input_square_matrices, Mat, multiply_matrices, Runner, SharedDataBuilder, TaskPoolCounters, TASKS_PREPARED, TASKS_SOLVED};

#[derive(Debug)]
pub struct BasicQueue<T> {
    head: Link<T>,
    tail: Link<T>
}

#[derive(Debug)]
pub struct Node<T> {
    val: T,
    next: Link<T>
}

impl<T> Node<T> {
    fn new(val: T) -> Self {
        Self {
            val,
            next: None
        }
    }
}

pub type Link<T> = Option<Arc<RefCell<Node<T>>>>;

impl<T> BasicQueue<T> {
    pub const fn new() -> Self {
        Self {
            head: None,
            tail: None
        }
    }
    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn pop(&mut self) -> Option<T> {
        let old_head = self.head.take();
        if let Some(n) = old_head {
            self.head = n.borrow_mut().next.take();
            if self.head.is_none() {
                self.tail = None;
            }
            let val = Arc::try_unwrap(n).ok().unwrap().into_inner().val;
            Some(val)
        }
        else {
            None
        }
    }
    pub fn push(&mut self, val: T) {
        let new_tail = Arc::new(RefCell::new(Node::new(val)));
        let old_tail = mem::replace(&mut self.tail, Some(new_tail.clone()));
        if let Some(n) = old_tail {
            n.borrow_mut().next = Some(new_tail);
        }
        else {
            self.head = Some(new_tail);
        }
    }
}

pub struct BlockingQueueRunner;
#[derive(Debug)]
pub struct BlockingQueueSharedData<T> {
    task_pool: Mutex<(TaskPoolCounters, BasicQueue<T>)>,
    consumer_waiter: Condvar,
}

impl<T> SharedDataBuilder for BlockingQueueSharedData<T> {
    fn new(producers_c: usize, consumers_c: usize, matrix_size: usize) -> Self {
        BlockingQueueSharedData {
            task_pool: Mutex::new((TaskPoolCounters::new(producers_c), BasicQueue::new())),
            consumer_waiter: Condvar::new()
        }
    }
}

impl Runner for BlockingQueueRunner {
    type SharedData = BlockingQueueSharedData<Self::Msg>;
    type Msg = (Mat, Mat);
    fn run_producer(mat_size: usize, shared_data: Arc<Self::SharedData>, i: usize) {
        let rand_mat = input_square_matrices(mat_size); // payload outside
        let mut guard = shared_data.task_pool.mylock();
        guard.1.push(rand_mat);
        guard.0.on_add_task();
        shared_data.consumer_waiter.notify_one();
        if guard.0.was_last_producer() {
            // println!("Notifying all consumers...");
            shared_data.consumer_waiter.notify_all();
        }
        drop(guard);
        // println!("Producer {} finished 1 task", i);
    }
    fn run_consumer(shared_data: Arc<Self::SharedData>, i: usize) {
        let mut guard = shared_data.task_pool.mylock();
        while guard.0.has_planned_tasks() { //exit condition, help to finish thread when there is no work to do
            if guard.1.is_empty() {
                // println!("\tConsumer {} is waiting...", i);
                guard = shared_data.consumer_waiter.mywait(guard);
                // println!("\tConsumer {} has finished wait", i)
            }
            else {

                let inp_data = guard.1.pop().unwrap();
                guard.0.on_take_task();

                drop(guard);
                // here data was taken from queue
                // TASKS_ACQUIRED.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
                // println!("\tConsumer {} got data", i);
                let res = multiply_matrices(inp_data).unwrap(); // payload outside
                TASKS_SOLVED.fetch_add(1, Ordering::SeqCst);
                // let filename = format!("res_{}_{}.txt", i, producers_c);
                // res.save_to_file(&filename);
                guard = shared_data.task_pool.mylock();
            }

        }
        // println!("\tConsumer {} has exited main loop!", i)
    }
}

// careful with this
unsafe impl<T> Send for BasicQueue<T> {}
