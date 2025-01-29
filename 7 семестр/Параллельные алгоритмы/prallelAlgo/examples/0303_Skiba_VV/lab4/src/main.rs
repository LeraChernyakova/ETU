use std::{thread, io::{stdin, stdout}, sync::{mpsc::channel, Arc}, ops::Range, cmp::min};


static WRITE_INPUT_METRIC: OnceLock<Instant> = OnceLock::new();
static MULTIPLY_METRIC: OnceLock<Instant> = OnceLock::new();
static WRITE_OUTPUT: OnceLock<Instant> = OnceLock::new();




use std::{io, fs::File};

use rand::Rng;

pub fn generate_random_matrix(rows: usize, cols: usize) -> Matrix {
    let mut vec = vec![0f64; rows * cols];
    let mut rng = rand::thread_rng();

    for i in 0..rows {
        for j in 0..cols {
            vec[i * cols + j] = rng.gen_range(0.0..100.0);
        }
    }

    Matrix::with_vector(vec, rows, cols)
}


pub fn input_matrices() -> (Matrix, Matrix) {

    print!("Enter the dimensions of the matrices (x1, y1/x2, y2): ");
    io::stdout().flush().expect("Failed to flush stdout");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read input");
    let dimensions: Vec<usize> = input
        .split_whitespace()
        .map(|s| s.parse().expect("Invalid input"))
        .collect();

    if dimensions.len() != 3 {
        println!("Invalid input, expected 3 integers separated by whitespace.");
        std::process::exit(1);
    }

    let rows0 = dimensions[0];
    let cols0 = dimensions[1];
    let cols1 = dimensions[2];

    let mat1 = generate_random_matrix(rows0, cols0);
    let mat2 = generate_random_matrix(cols0, cols1);

    (mat1, mat2)
}

use std::{time::Instant, sync::OnceLock};
use std::io::Write;
use lab4::Matrix;
use lab4::par_mult::mult_par_strassen;

pub fn start_measure(cell: &'static OnceLock<Instant>) {
    cell.set(std::time::Instant::now()).unwrap();
}

pub fn stop_measure(cell: &'static OnceLock<Instant>) -> std::time::Duration {
    let now = std::time::Instant::now();

    now - *cell.get().unwrap()
}


fn input_worker() {
    let (mat1, mat2) = input_matrices();

    if cfg!(feature="multithreaded") {
        print!("Input multiplication workers count: ");
        std::io::Write::flush(&mut stdout()).unwrap();

        let mut buf = String::new();
        stdin().read_line(&mut buf).unwrap();
        let mut workers_cnt = buf.trim().parse().expect("Invalid workers count!");

        let mat_elem_cnt = mat1.rows * mat2.cols;
        if workers_cnt > mat_elem_cnt {
            println!("Workers count is more than matrix elements count, setting workers count to {}", mat_elem_cnt);
            workers_cnt = mat_elem_cnt;
        }

        multiply_worker_multithreaded((mat1, mat2), workers_cnt);
    } else if cfg!(feature="strassen") {
        start_measure(&MULTIPLY_METRIC);
        let res = mult_par_strassen(&mat1, &mat2);


        let elapsed = stop_measure(&MULTIPLY_METRIC);
        println!(" > Multiply matrices: Elapsed time: {} ms", elapsed.as_millis());
    }

}

fn multiply_worker_multithreaded((mat1, mat2): (Matrix, Matrix), worker_cnt: usize) {
    //here we create MPSC channel and deligate work to P workers

    start_measure(&MULTIPLY_METRIC);
    let res_rows = mat1.rows;
    let res_cols = mat2.cols;
    let mut res = vec![vec![0f64; res_cols]; res_rows];

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
    let (tx, rx) = channel::<(Range<usize>, Box<[f64]>)>();
    // send it back to main thread

    // how much elements each worker should calculate
    let chunk_size = mat_elem_cnt / worker_cnt;

    // define function for workers
    let calculate_rng = move |rng: Range<usize>, mat1: Arc<Matrix>, mat2: Arc<Matrix>| -> Box<[f64]> {
        // here we calculate range of matrix and send it to main thread using channel (see below in thread::spawn)
        let mut chunk: Vec<f64> = Vec::with_capacity(rng.len());

        for cursor in rng.clone() {
            let row = cursor / res_cols;
            let col = cursor % res_cols;

            let mut sum = 0f64;
            for i in 0..mat2.rows {
                sum += mat1.at(row, i) * mat2.at(i, col);
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
}



fn main() {
    let mut m = Matrix::new(20, 20);
    println!("\n\t\t*** Matrix multiplication [multithread version] ***");
    input_worker();
}
