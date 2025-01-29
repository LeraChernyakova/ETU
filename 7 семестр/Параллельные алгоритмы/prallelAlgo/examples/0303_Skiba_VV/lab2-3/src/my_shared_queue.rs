use std::{sync::Arc, mem};
use crossbeam::queue::SegQueue;
use crate::{input_square_matrices, Mat, multiply_matrices, Runner, SharedDataBuilder, SharedQueue, TaskPoolCounters};

use crate::custom_sync_primitieves::*;
use std::fmt::Debug;

#[derive(Debug)]
pub struct MySharedQueue<T> where T: Debug {
    head: MySharedQueueLink<T>,
    tail: MySharedQueueLink<T>
}

pub type MySharedQueueLink<T> = Mutex<Option<Arc<SharedQueueNode<T>>>>;


#[derive(Debug)]
pub struct SharedQueueNode<T> {
    val: T,
    next: MySharedQueueLink<T>
}

impl<T: Debug> SharedQueueNode<T> {
    pub fn new(val: T) -> Self {
        Self {
            val,
            next: Mutex::new(None)
        }
    }
}


impl<T: Debug> SharedQueue for MySharedQueue<T> {
    type Item = T;

    fn new() -> Self {
        Self {
            head: Mutex::new(None),
            tail: Mutex::new(None)
        }
    }

    fn push(&self, val: T) {

        let new_tail = Arc::new(SharedQueueNode::new(val));

        let mut tail_guard = self.tail.mylock();

        if let Some(old_tail) = tail_guard.take() {
            *old_tail.next.mylock() = Some(new_tail.clone());
        } else {
            *self.head.mylock() = Some(new_tail.clone());
        }

        *tail_guard = Some(new_tail);
    }

    fn pop(&self) -> Option<T> {
        let mut head_guard = self.head.mylock();

        if let Some(old_head) = head_guard.take() {
            *head_guard = old_head.next.mylock().take();
            if head_guard.is_none() {
                *self.tail.mylock() = None;
            }

            return Some(Arc::try_unwrap(old_head).unwrap().val)
        }

        None
    }

    fn is_empty(&self) -> bool {
        self.head.mylock().is_none()
    }
}

impl<T: Debug> Drop for MySharedQueue<T> {
    fn drop(&mut self) {
        while self.pop().is_some() {}
    }
}