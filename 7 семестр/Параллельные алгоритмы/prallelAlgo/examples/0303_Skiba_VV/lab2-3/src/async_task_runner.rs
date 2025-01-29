use std::sync::atomic::{AtomicUsize, Ordering};
use std::thread;
use std::time::{Duration, Instant};
use async_channel::{bounded, unbounded};
use crossbeam::sync::WaitGroup;
use futures::executor::block_on;
use tokio::sync::oneshot;
use crate::{input_square_matrices, Mat, multiply_matrices, TASKS_PREPARED, TASKS_SOLVED, TASKS_TOTAL};


pub async fn async_run_tasks(tasks_c: usize, workers_c: usize, mat_size: usize) -> Duration {
    let (tx, rx) = bounded::<(Mat, Mat, oneshot::Sender<Mat>)>(tasks_c);

    TASKS_PREPARED.store(0, Ordering::Relaxed);
    TASKS_SOLVED.store(0, Ordering::Relaxed);
    TASKS_TOTAL.store(tasks_c, Ordering::Relaxed);

    let start = Instant::now();

    // Producers
    let producers: Vec<_> = (0..tasks_c).map(|i| {
        let tx = tx.clone();
        tokio::spawn(async move {
            let rand_mat = input_square_matrices(mat_size); // payload outside
            let (res_tx, res_rx) = oneshot::channel();
            tx.send((rand_mat.0, rand_mat.1, res_tx)).await.unwrap();
            TASKS_PREPARED.fetch_add(1, Ordering::Relaxed);
            let res = res_rx.await.unwrap();
            TASKS_SOLVED.fetch_add(1, Ordering::Relaxed);

        })
    }).collect();

    let wg = WaitGroup::new();
    // Consumers
    for i in 0..workers_c {
        let rx = rx.clone();
        let wg = wg.clone();
        thread::spawn(move || {
            loop {
                if rx.is_closed(){
                    break;
                }
                let _ = rx.recv_blocking().and_then(|r| {
                    let res = multiply_matrices((r.0, r.1)).unwrap();
                    r.2.send(res).unwrap();
                    Ok(())
                });
            }
            drop(wg);
        });
    };

    // Wait for all tasks to complete
    for p in producers {
        p.await.unwrap()
    }

    // Drop the sender to indicate that no more items will be sent on the channel
    drop(tx);

    println!("Waiting for all consumers...");
    wg.wait();

    assert_eq!(TASKS_PREPARED.load(Ordering::SeqCst), tasks_c);
    assert_eq!(TASKS_SOLVED.load(Ordering::SeqCst), tasks_c);

    start.elapsed()
}