use std::thread;

use workers::*;

use std::{time::Instant, sync::OnceLock};

static WRITE_INPUT_METRIC: OnceLock<Instant> = OnceLock::new();
static MULTIPLY_METRIC: OnceLock<Instant> = OnceLock::new();
static WRITE_OUTPUT: OnceLock<Instant> = OnceLock::new();

fn input_worker() {
    println!("\tINPUT WORKER START");
    let (mat1, mat2) = input_matrices();

    start_measure(&WRITE_INPUT_METRIC);

    mat1.save_to_file("in1.txt");
    mat2.save_to_file("in2.txt");

    let elapsed = stop_measure(&WRITE_INPUT_METRIC);
    println!(" > Write inputs to file: Elapsed time: {} ms", elapsed.as_millis());

    thread::spawn(move || {
        multiply_worker((mat1, mat2));
    })
    .join()
    .unwrap();

    println!("\tINPUT WORKER END");
}

fn multiply_worker(inp_data: (Mat, Mat)) {
    println!("\tMULTIPLY WORKER START");

    start_measure(&MULTIPLY_METRIC);
    let res = multiply_matrices(inp_data);
    let elapsed = stop_measure(&MULTIPLY_METRIC);
    println!(" > Multiply matrices: Elapsed time: {} ms", elapsed.as_millis());


    let Some(res) = res else {
        return;
    };

    println!("Spawning save worker...");

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
    println!("\n\t\t*** Matrix multiplication [threads version] ***");
    input_worker();
}
