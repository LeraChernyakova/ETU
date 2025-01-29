

#[cfg(feature = "advanced_sync")]
pub use parking_lot::{Mutex, Condvar, MutexGuard};

#[cfg(not(feature = "advanced_sync"))]
pub use std::sync::{Mutex, Condvar, MutexGuard};

pub trait MyMutex<T> {
    fn mylock(&self) -> MutexGuard<T>;
    fn my_into_inner(self) -> T;
}

pub trait MyCondVar<'a, T> {
    fn mywait(&self, guard: MutexGuard<'a, T>) -> MutexGuard<'a, T>;
}

#[cfg(not(feature = "advanced_sync"))]
impl<T> MyMutex<T> for Mutex<T> {
    fn mylock(&self) -> MutexGuard<T> {
        self.lock().unwrap()
    }
    fn my_into_inner(self) -> T {
        self.into_inner().unwrap()
    }
}

#[cfg(feature = "advanced_sync")]
impl<T> MyMutex<T> for Mutex<T> {
    fn mylock(&self) -> MutexGuard<T> {
        self.lock()
    }
    fn my_into_inner(self) -> T {
        self.into_inner()
    }
}

#[cfg(not(feature = "advanced_sync"))]
impl<'a, T> MyCondVar<'a, T> for Condvar {
    fn mywait(&self, guard: MutexGuard<'a, T>) -> MutexGuard<'a, T> {
        self.wait(guard).unwrap()
    }
}

#[cfg(feature = "advanced_sync")]
impl<'a, T> MyCondVar<'a, T> for Condvar {
    fn mywait(&self, mut guard: MutexGuard<'a, T>) -> MutexGuard<'a, T> {
        self.wait(&mut guard);
        guard
    }
}