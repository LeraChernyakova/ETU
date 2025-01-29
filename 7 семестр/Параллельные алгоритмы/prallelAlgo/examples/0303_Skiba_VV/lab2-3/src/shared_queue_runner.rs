use std::sync::Arc;
use std::sync::atomic::Ordering;
use std::thread::park;
use crossbeam::sync::WaitGroup;
use crossbeam::utils::Backoff;
use crate::{input_square_matrices, Mat, multiply_matrices, Runner, SharedDataBuilder, TaskPoolCounters, TASKS_PREPARED, TASKS_SOLVED, TASKS_TOTAL};
use crate::custom_sync_primitieves::*;

pub trait SharedQueue {
    type Item;
    fn new() -> Self;
    fn push(&self, val: Self::Item);
    fn pop(&self) -> Option<Self::Item>;
    fn is_empty(&self) -> bool;
}


pub struct SharedQueueRunner<Q: SharedQueue> {
    _phantom: std::marker::PhantomData<Q>
}
#[derive(Debug)]
pub struct SharedQueueSharedData<Q> {
    task_pool_counters: Mutex<TaskPoolCounters>,
    consumer_waiter: Condvar,
    shared_queue: Q,
}

impl<Q> SharedDataBuilder for SharedQueueSharedData<Q>
    where Q: SharedQueue {
    fn new(producers_c: usize, consumers_c: usize, matrix_size: usize) -> Self {
        SharedQueueSharedData {
            task_pool_counters: Mutex::new(TaskPoolCounters::new(producers_c)),
            consumer_waiter: Condvar::new(),
            shared_queue: Q::new()
        }
    }
}

impl<Q: SharedQueue<Item = (Mat, Mat)> + Sync + Send + 'static> Runner for SharedQueueRunner<Q> {
    type SharedData = SharedQueueSharedData<Q>;
    type Msg = (Mat, Mat);
    fn run_producer(mat_size: usize, shared_data: Arc<Self::SharedData>, i: usize) {
        let rand_mat = input_square_matrices(mat_size); // payload outside
        // println!("Producer {}: Task work done!", i);
        let mut guard = shared_data.task_pool_counters.mylock();
        // println!("Producer {}: Lock acquired...", i);
        shared_data.shared_queue.push(rand_mat);
        guard.on_add_task();
        shared_data.consumer_waiter.notify_one();
        if guard.was_last_producer() {
            // println!("Producer {}: Notifying all consumers...", i);
            shared_data.consumer_waiter.notify_all();
        }
        drop(guard);
        // println!("Producer {} finished 1 task, lock released", i);
    }
    fn run_consumer(shared_data: Arc<Self::SharedData>, i: usize) {
        // println!("\tConsumer {}: running...", i);
        let mut guard = shared_data.task_pool_counters.mylock();
        // println!("\tConsumer {}: Lock acquired...", i);
        while guard.has_planned_tasks() { //exit condition, help to finish thread when there is no work to do
            if shared_data.shared_queue.is_empty() {
                // println!("\tConsumer {}: waiting...", i);
                guard = shared_data.consumer_waiter.mywait(guard);
                // println!("\tConsumer {} has finished wait", i)
            }
            else {
                let inp_data = shared_data.shared_queue.pop().unwrap();
                guard.on_take_task();

                drop(guard);
                // here data was taken from queue
                // println!("\tConsumer {}: got data, lock released", i);
                let res = multiply_matrices(inp_data).unwrap(); // payload outside
                TASKS_SOLVED.fetch_add(1, Ordering::SeqCst);
                // let filename = format!("res_{}_{}.txt", i, producers_c);
                // res.save_to_file(&filename);
                guard = shared_data.task_pool_counters.mylock();
                // println!("\tConsumer {}: got data, lock reacquired", i);
            }

        }
        // println!("\tConsumer {} has exited main loop!", i);
    }
}


pub struct ParkerSharedQueueRunner<Q: SharedQueue> {
    _phantom: std::marker::PhantomData<Q>
}

#[derive(Debug)]
pub struct ParkerSharedQueueSharedData<Q> {
    shared_queue: Q,
    wg: Arc<Option<WaitGroup>>,
}

impl<Q> SharedDataBuilder for ParkerSharedQueueSharedData<Q>
    where Q: SharedQueue {
    fn new(producers_c: usize, consumers_c: usize, matrix_size: usize) -> Self {
        ParkerSharedQueueSharedData {
            shared_queue: Q::new(),
            wg: Arc::new(Some(WaitGroup::new()))
        }
    }
}


impl<Q: SharedQueue<Item = (Mat, Mat)> + Sync + Send + 'static> Runner for ParkerSharedQueueRunner<Q> {
    type SharedData = ParkerSharedQueueSharedData<Q>;
    type Msg = (Mat, Mat);
    fn run_producer(mat_size: usize, shared_data: Arc<Self::SharedData>, i: usize) {
        // println!("producer running...");
        let rand_mat = input_square_matrices(mat_size);
        shared_data.shared_queue.push(rand_mat);
        // println!("one task prepared")
    }
    fn run_consumer(shared_data: Arc<Self::SharedData>, i: usize) {
        // println!("consumer running...");
        let backoff = Backoff::new();
        loop { //exit condition, help to finish thread when there is no work to do
            if shared_data.shared_queue.is_empty() {
                // println!("queue is empty, snoozing...");
                backoff.snooze();
            }
            else {
                // println!("Trying to pop element...");
                backoff.reset();
                if let Some(inp_data) = shared_data.shared_queue.pop() {
                    // println!("Got element");

                    let res = multiply_matrices(inp_data).unwrap();
                    TASKS_SOLVED.fetch_add(1, Ordering::SeqCst);
                    // println!("one task solved");
                    // let filename = format!("res_{}_{}.txt", i, producers_c);
                    // res.save_to_file(&filename);
                }
            }

            if backoff.is_completed() {
                // println!("Backoff completed! check exit condition...");
                if TASKS_SOLVED.load(Ordering::Relaxed) == TASKS_TOTAL.load(Ordering::Relaxed) && shared_data.shared_queue.is_empty() {
                    // println!("exit condition reached");
                    break; // finish of this worker
                }
            }
        }
    }
}