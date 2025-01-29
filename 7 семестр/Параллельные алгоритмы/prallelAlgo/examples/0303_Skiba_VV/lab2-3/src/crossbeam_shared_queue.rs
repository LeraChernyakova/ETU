use crossbeam::queue::SegQueue;
use crate::SharedQueue;


impl<T> SharedQueue for SegQueue<T> {
    type Item = T;

    fn new() -> Self {
        Self::new()
    }
    fn push(&self, data: T) {
        self.push(data);
    }

    fn pop(&self) -> Option<T> {
        self.pop()
    }

    fn is_empty(&self) -> bool {
        self.is_empty()
    }
}