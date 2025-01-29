use std::cell::RefCell;
use std::error::Error;
use std::io::{stdin, stdout, Write};
use std::sync::atomic::AtomicUsize;
use std::sync::{Mutex, Arc, Condvar};
use std::{thread, mem};
use std::thread::JoinHandle;
use std::time::{Duration, Instant};

use crossbeam::queue::SegQueue;

use lab2::{BasicQueue, MySharedQueue, input_square_matrices, multiply_matrices, MatExt, TaskPoolCounters, run_tasks, BlockingQueueRunner, LockFreeQueue, async_run_tasks};


fn main() -> anyhow::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let producers_c = args.get(1).map(|s| s.parse::<usize>().unwrap()).unwrap_or(40);
    let consumers_c = args.get(2).map(|s| s.parse::<usize>().unwrap()).unwrap_or(100);
    let matrix_size = args.get(3).map(|s| s.parse::<usize>().unwrap()).unwrap_or(50);

    println!("Running with {} producer(s), {} consumer(s), matrix size {}...", producers_c, consumers_c, matrix_size);

    #[cfg(not(feature="parking-backoff-runner"))]
    use lab2::SharedQueueRunner as SharedQueueRunner;
    #[cfg(feature="parking-backoff-runner")]
    use lab2::ParkerSharedQueueRunner as SharedQueueRunner;

    #[cfg(feature="crossbeam_queue")]
    {
        println!("Running SharedQueueRunner using SegQueue...");
        let dur = run_tasks::<SharedQueueRunner<SegQueue<_>>>(producers_c, consumers_c, matrix_size);
        println!("Executing all tasks took {:?}!", dur);
    }

    #[cfg(feature="my_shared_queue")]
    {
        println!("Running SharedQueueRunner using MySharedQueue...");
        let dur = run_tasks::<SharedQueueRunner<MySharedQueue<_>>>(producers_c, consumers_c, matrix_size);
        println!("Executing all tasks took {:?}!", dur);
    }

    #[cfg(feature="lock_free_queue")]
    {
        println!("Running SharedQueueRunner using MyLockFreeQueue...");
        let dur = run_tasks::<SharedQueueRunner<LockFreeQueue<_>>>(producers_c, consumers_c, matrix_size);
        println!("Executing all tasks took {:?}!", dur);
    }

    #[cfg(feature="my_blocking_queue")]
    {
        println!("Running BlockingQueuerunner`...");
        let dur = run_tasks::<BlockingQueueRunner>(producers_c, consumers_c, matrix_size);
        println!("Executing all tasks took {:?}!", dur);
    }

    #[cfg(feature="async_channels_threads")]
    {
        println!("Running async runner...");
        let dur = tokio::runtime::Builder::new_current_thread().build().unwrap().block_on(async move {
            async_run_tasks(producers_c, consumers_c, matrix_size).await
        });
        println!("Executing all tasks took {:?}!", dur);
    }

    Ok(())
}