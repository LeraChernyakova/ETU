use std::sync::atomic::{AtomicPtr, AtomicUsize, Ordering};
use crate::SharedQueue;

pub struct LockFreeQueue<T> {
    queue: lockfree::queue::Queue<T>,
    cnt: AtomicUsize
}


impl<T> SharedQueue for LockFreeQueue<T> {
    type Item = T;

    fn new() -> Self {
        Self {
            queue: lockfree::queue::Queue::new(),
            cnt: AtomicUsize::new(0)
        }
    }
    fn push(&self, data: T) {
        self.queue.push(data);
        self.cnt.fetch_add(1, Ordering::SeqCst);
    }

    fn pop(&self) -> Option<T> {
        match self.queue.pop() {
            Some(v) => {
                self.cnt.fetch_sub(1, Ordering::SeqCst);
                Some(v)
            }
            None => None,
        }
    }

    fn is_empty(&self) -> bool {
        self.cnt.load(Ordering::SeqCst) == 0
    }
}