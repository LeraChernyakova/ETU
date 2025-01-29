use std::{thread, io::{stdin, stdout}, sync::{mpsc::channel, Arc}, ops::Range, cmp::min};

use workers::*;

use std::{time::Instant, sync::OnceLock};

static WRITE_INPUT_METRIC: OnceLock<Instant> = OnceLock::new();
static MULTIPLY_METRIC: OnceLock<Instant> = OnceLock::new();
static WRITE_OUTPUT: OnceLock<Instant> = OnceLock::new();


fn input_worker() {
    println!("\tINPUT WORKER START");
    let (mat1, mat2) = input_matrices();

    print!("Input multiplication workers count: ");
    std::io::Write::flush(&mut stdout()).unwrap();

    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let mut workers_cnt = buf.trim().parse().expect("Invalid workers count!");

    let mat_elem_cnt = mat1.len() * mat2[0].len();
    if workers_cnt > mat_elem_cnt {
        println!("Workers count is more than matrix elements count, setting workers count to {}", mat_elem_cnt);
        workers_cnt = mat_elem_cnt;
    }

    start_measure(&WRITE_INPUT_METRIC);

    mat1.save_to_file("in1.txt");
    mat2.save_to_file("in2.txt");

    let elapsed = stop_measure(&WRITE_INPUT_METRIC);
    println!(" > Write inputs to file: Elapsed time: {} ms", elapsed.as_millis());

    thread::spawn(move || {
        multiply_worker((mat1, mat2), workers_cnt);
    })
    .join()
    .unwrap();

    println!("\tINPUT WORKER END");
}

fn multiply_worker((mat1, mat2): (Mat, Mat), worker_cnt: usize) {
    println!("\tMULTIPLY WORKER START");
    //here we create MPSC channel and deligate work to P workers

    start_measure(&MULTIPLY_METRIC);
    let res_rows = mat1.len();
    let res_cols = mat2[0].len();
    let mut res = vec![vec![0; res_cols]; res_rows];

    // Wrap matrices into Arc - atomic reference counter, 
    // so we can share them read-only between threads

    // Otherwise, it would be a compile error, because local 
    // variables lifetime may be shorter than lifetime of spawned thread (possible dangling pointer)
    let mat1 = Arc::new(mat1);
    let mat2 = Arc::new(mat2);

    let mat_elem_cnt = res_rows * res_cols;

    // We use MPSC channel for sending multiplied result back from workers to this thread
    // rx lives here
    // tx is cloned and sent to workers
    let (tx, rx) = channel::<(Range<usize>, Box<[i32]>)>();
                                                   // send it back to main thread

    // how much elements each worker should calculate
    let chunk_size = mat_elem_cnt / worker_cnt;

    // define function for workers
    let calculate_rng = move |rng: Range<usize>, mat1: Arc<Mat>, mat2: Arc<Mat>| -> Box<[i32]> {
        // here we calculate range of matrix and send it to main thread using channel (see below in thread::spawn)
        let mut chunk: Vec<i32> = Vec::with_capacity(rng.len());

        for cursor in rng.clone() {
            let row = cursor / res_cols;
            let col = cursor % res_cols;

            let mut sum = 0;
            for i in 0..mat2.len() {
                sum += mat1[row][i] * mat2[i][col];
            }

            chunk.push(sum);
        }

        chunk.into_boxed_slice()
    };

    let mut cursor = 0;
    while cursor < mat_elem_cnt {
        let tx_copy = tx.clone();

        let rng = cursor..min(cursor + chunk_size, mat_elem_cnt);
        cursor += chunk_size;

        println!("Sending range {}..{}", rng.start, rng.end);

        let mat1_clone = mat1.clone();
        let mat2_clone = mat2.clone();

        std::thread::spawn(move || {
            //calculate chunk of res matrix data
            let calculated_chunk = calculate_rng(rng.clone(), mat1_clone, mat2_clone);
            //send it to caller thread to update result matrix
            tx_copy.send((rng, calculated_chunk)).unwrap();
        });
    }

    // drop tx to close sender in this thread, leave only cloned senders in worker threads
    // so, when all workers finish their work, they gonna drop sender and loop below will finish
    // Make use of channels allows us to avoid joining all of the workers and possibly improve performance!
    drop(tx);

    println!("Collecting results...");

    // Receiving chunks of result matrix from spawned workers...
    while let Ok((rng, chunk)) = rx.recv() {
        print!(".");
        std::io::Write::flush(&mut stdout()).unwrap();
        for cursor in rng.clone() {
            let row = cursor / res_cols;
            let col = cursor % res_cols;

            res[row][col] = chunk[cursor - rng.start];
        }
    }

    let elapsed = stop_measure(&MULTIPLY_METRIC);
    println!(" > Multiply matrices: Elapsed time: {} ms", elapsed.as_millis());


    println!("Finished! Launching save worker...");
    thread::spawn(move || {
        save_worker(res);
    })
    .join()
    .unwrap();

    println!("\tMULTIPLY WORKER END");
}

fn save_worker(mat: Mat) {
    println!("\tSAVE WORKER START");
    start_measure(&WRITE_OUTPUT);

    mat.save_to_file("res.txt");

    let elapsed = stop_measure(&WRITE_OUTPUT);
    println!(" > Write output to file: Elapsed time: {} ms", elapsed.as_millis());

    println!("Result matrix saved to res.txt");
    println!("\tSAVE WORKER END");
}


fn main() {
    println!("\n\t\t*** Matrix multiplication [threads optimized version] ***");
    input_worker();
}
