use std::{io, fs::File};


use rand::Rng;

pub trait MatExt {
    fn save_to_file(&self, name: &str);
}
pub type Mat = Vec<Vec<i32>>;

use io::Write;

impl MatExt for  Mat {
    fn save_to_file(&self, name: &str) {
        let mut file = File::create(name).expect("Failed to create res.txt");

        for row in self {
            for &element in row {
                write!(file, "{} ", element).expect("Failed to write to file");
            }
            writeln!(file).expect("Failed to write to file");
        }
    }
}

pub fn generate_random_matrix(rows: usize, cols: usize) -> Mat {
    let mut rng = rand::thread_rng();
    let mut mat = Vec::new();

    // println!("Filling matrix {}x{} with random values (1..10)...", rows, cols);

    for _ in 0..rows {
        let row: Vec<i32> = (0..cols).map(|_| rng.gen_range(1..10)).collect();
        mat.push(row);
    }

    mat
}


pub fn input_matrices() -> (Mat, Mat) {

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

pub fn input_square_matrices(n: usize) -> (Mat, Mat) {

    let dimensions = [n,n,n];

    let rows0 = dimensions[0];
    let cols0 = dimensions[1];
    let cols1 = dimensions[2];

    let mat1 = generate_random_matrix(rows0, cols0);
    let mat2 = generate_random_matrix(cols0, cols1);

    (mat1, mat2)
}

pub fn multiply_matrices((mat1, mat2): (Mat, Mat)) -> Option<Mat> {

    if mat1.is_empty() || mat2.is_empty() || mat1[0].len() != mat2.len() {
        println!("Matrix multiplication is not possible with the given matrices.");
        return None;
    }

    let rows = mat1.len();
    let cols = mat2[0].len();
    let mut res = vec![vec![0; cols]; rows];

    for i in 0..rows {
        for j in 0..cols {
            for k in 0..mat1[0].len() {
                res[i][j] += mat1[i][k] * mat2[k][j];
            };
        }
    }

    Some(res)
}

use std::{time::Instant, sync::OnceLock};

pub fn start_measure(cell: &'static OnceLock<Instant>) {
    cell.set(std::time::Instant::now()).unwrap();
}

pub fn stop_measure(cell: &'static OnceLock<Instant>) -> std::time::Duration {
    let now = std::time::Instant::now();

    now - *cell.get().unwrap()
}
