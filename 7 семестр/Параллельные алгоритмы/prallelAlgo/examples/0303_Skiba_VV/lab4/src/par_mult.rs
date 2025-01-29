pub use crate::Matrix;
pub use crate::mult::*;
use rand::thread_rng;
use threadpool::ThreadPool;
use std::sync::{Arc, Mutex};

static mut TEST_STATE:bool = false;

/**
 * Strassen algorithm. See https://en.wikipedia.org/wiki/Strassen_algorithm
 * Breaks the provided matrices down into 7 smaller submatrices for multiplication, which results in
 * smaller asymptotic complexity of around O(n^2.8), at the expense of a higher scalar constant due to the extra work required.
 * Falls back to the transpose naive multiplication method if row and column dimensions are 64 or less.
 * Recurses as input matrices are broken down and this algorithm is run further on those submatrices.
 * Panics if matrices `a` and `b` are of incompatbile dimensions.
 */
pub fn
mult_par_strassen (a: &Matrix, b: &Matrix) -> Matrix {

    if a.cols != b.rows {
        panic!("Matrix sizes do not match");
    }

    let mut max_dimension = a.rows;

    // Find the largest row or column dimension across `a` and `b`
    if a.cols >= a.rows && a.cols >= b.cols {
        max_dimension = a.cols;
    } else if b.rows >= b.cols && b.rows >= a.rows {
        max_dimension = b.rows;
    } else if b.cols >= b.rows && b.cols >= a.cols {
        max_dimension = b.cols;
    }

    // If the largest dimension is odd, we'll add one and then pad the matrix to make it
    // an even number of rows and columns
    if max_dimension % 2 == 1 {
        max_dimension += 1;
    }

    let pool = ThreadPool::new(7);

    if a.is_square() && b.is_square() && a.rows == max_dimension {
        // The matrices are square; proceed
        return _mult_par_strassen(&a, &b, &pool);
    } else {
        // Pad `a` and `b` to `max_dimension` and pass to underlying function `_mult_strassen`. Strip out
        // extra padded rows and columns after that operation is complete.
        return _mult_par_strassen(
            &a.pad(max_dimension),
            &b.pad(max_dimension),
            &pool
        ).reduce(a.rows, a.rows);
    }
}

/**
 * Inner parallel Strassen algorithm logic.
 */
fn
_mult_par_strassen (a: &Matrix, b: &Matrix, pool: &ThreadPool) -> Matrix {

    unsafe {
        // Ugly hack for enabling recursion testing in unit tests.
        // If not test state, fall back to transpose matrix multiplication if
        // input Matrix rows and columns are 64 or less.
        if (!TEST_STATE && a.rows <= 64) || (TEST_STATE && a.rows <= 2) {
            return mult_transpose(a, b);
        }
    }

    /* This will be the row and column size of the submatrices */
    let m = a.rows / 2;

    /* Top left submatrix */
    let tl_row_start = 0;
    let tl_col_start = 0;

    /* Top right submatrix */
    let tr_row_start = 0;
    let tr_col_start = m;

    /* Bottom left submatrix */
    let bl_row_start = m;
    let bl_col_start = 0;

    /* Bottom right submatrix */
    let br_row_start = m;
    let br_col_start = m;

    /* Vectors for 7 submatrices of `a` */
    let mut aa1 = Vec::with_capacity(m * m);
    let mut aa2 = Vec::with_capacity(m * m);
    let mut aa3 = Vec::with_capacity(m * m);
    let mut aa4 = Vec::with_capacity(m * m);
    let mut aa5 = Vec::with_capacity(m * m);
    let mut aa6 = Vec::with_capacity(m * m);
    let mut aa7 = Vec::with_capacity(m * m);

    /* Vectors for 7 submatrices of `b` */
    let mut bb1 = Vec::with_capacity(m * m);
    let mut bb2 = Vec::with_capacity(m * m);
    let mut bb3 = Vec::with_capacity(m * m);
    let mut bb4 = Vec::with_capacity(m * m);
    let mut bb5 = Vec::with_capacity(m * m);
    let mut bb6 = Vec::with_capacity(m * m);
    let mut bb7 = Vec::with_capacity(m * m);

    /* Initializes submatrices of `a` based on its quadrants, the manner described below */

    /* AA1 = (A1,1 + A2,2) */
    submatrix_add (&mut aa1, a, tl_row_start, tl_col_start, br_row_start, br_col_start, m);
    /* AA2 = (A2,1 + A2,2) */
    submatrix_add (&mut aa2, a, bl_row_start, bl_col_start, br_row_start, br_col_start, m);
    /* AA3 = (A1,1) */
    submatrix_cpy (&mut aa3, a, tl_row_start, tl_col_start, m);
    /* AA4 = (A2,2) */
    submatrix_cpy (&mut aa4, a, br_row_start, br_col_start, m);
    /* AA5 = (A1,1 + A1,2) */
    submatrix_add (&mut aa5, a, tl_row_start, tl_col_start, tr_row_start, tr_col_start, m);
    /* AA6 = (A2,1 - A1,1) */
    submatrix_sub (&mut aa6, a, bl_row_start, bl_col_start, tl_row_start, tl_col_start, m);
    /* AA7 = (A1,2 - A2,2) */
    submatrix_sub (&mut aa7, a, tr_row_start, tr_col_start, br_row_start, br_col_start, m);

    /* Initializes submatrices of `b` based on its quadrants, the manner described below */

    /* BB1 = (B1,1 + B2,2) */
    submatrix_add (&mut bb1, b, tl_row_start, tl_col_start, br_row_start, br_col_start, m);
    /* BB2 = (B1,1) */
    submatrix_cpy (&mut bb2, b, tl_row_start, tl_col_start, m);
    /* BB3 = (B1,2 - B2,2) */
    submatrix_sub (&mut bb3, b, tr_row_start, tr_col_start, br_row_start, br_col_start, m);
    /* BB4 = (B2,1 - B1,1) */
    submatrix_sub (&mut bb4, b, bl_row_start, bl_col_start, tl_row_start, tl_col_start, m);
    /* BB5 = (B2,2) */
    submatrix_cpy (&mut bb5, b, br_row_start, br_col_start, m);
    /* BB6 = (B1,1 + B1,2) */
    submatrix_add (&mut bb6, b, tl_row_start, tl_col_start, tr_row_start, tr_col_start, m);
    /* BB7 = (B2,1 + B2,2) */
    submatrix_add (&mut bb7, b, bl_row_start, bl_col_start, br_row_start, br_col_start, m);

    /*
     * The output matrix C is expressed in terms of the block matrices M1..M7
     *
     * C1,1 = M1 + M4 - M5 + M7
     * C1,2 = M3 + M5
     * C2,1 = M2 + M4
     * C2,2 = M1 - M2 + M3 + M6
     *
     * Each of the block matrices M1..M7 is composed of quadrants from A and B as follows:
     *
     * M1 = AA[0] * BB[0] = (A1,1 + A2,2)(B1,1 + B2,2)
     * M2 = AA[1] * BB[1] = (A2,1 + A2,2)(B1,1)
     * M3 = AA[2] * BB[2] = (A1,1)(B1,2 - B2,2)
     * M4 = AA[3] * BB[3] = (A2,2)(B2,1 - B1,1)
     * M5 = AA[4] * BB[4] = (A1,1 + A1,2)(B2,2)
     * M6 = AA[5] * BB[5] = (A2,1 - A1,1)(B1,1 + B1,2)
     * M7 = AA[6] * BB[6] = (A1,2 - A2,2)(B2,1 + B2,2)
     *
     * The following operations each recurse further, passing their respective submatrices into the
     * main `mult_strassen` function above.
     */
    let async_m1 = _par_run_strassen(aa1, bb1, m, pool);
    let async_m2 = _par_run_strassen(aa2, bb2, m, pool);
    let async_m3 = _par_run_strassen(aa3, bb3, m, pool);
    let async_m4 = _par_run_strassen(aa4, bb4, m, pool);
    let async_m5 = _par_run_strassen(aa5, bb5, m, pool);
    let async_m6 = _par_run_strassen(aa6, bb6, m, pool);
    let async_m7 = _par_run_strassen(aa7, bb7, m, pool);

    // Wait for threads
    pool.join();

    // Extract worker thread results from ugly nested structs
    let mut m1 = Arc::try_unwrap(async_m1).ok().unwrap().into_inner().unwrap().unwrap();
    let m2 = Arc::try_unwrap(async_m2).ok().unwrap().into_inner().unwrap().unwrap();
    let m3 = Arc::try_unwrap(async_m3).ok().unwrap().into_inner().unwrap().unwrap();
    let mut m4 = Arc::try_unwrap(async_m4).ok().unwrap().into_inner().unwrap().unwrap();
    let mut m5 = Arc::try_unwrap(async_m5).ok().unwrap().into_inner().unwrap().unwrap();
    let m6 = Arc::try_unwrap(async_m6).ok().unwrap().into_inner().unwrap().unwrap();
    let mut m7 = Arc::try_unwrap(async_m7).ok().unwrap().into_inner().unwrap().unwrap();

    /* C1,1 = M1 + M4 - M5 + M7 */
    let m11 = m7.sub(&m5).add(&m4).add(&m1);

    /* C1,2 = M3 + M5 */
    let m12 = m5.add(&m3);

    /* C2,1 = M2 + M4 */
    let m21 = m4.add(&m2);

    /* C2,2 = M1 - M2 + M3 + M6 */
    let m22 = m1.sub(&m2).add(&m3).add(&m6);

    /* Return a single matrix composing each of these four matrices as quadrants */
    return reconstitute(&m11, &m12, &m21, &m22, m, a.rows);
}

/**
 * Execute a recursive strassen multiplication of the given vectors, from a thread contained
 * within the provided thread pool.
 */
fn
_par_run_strassen (a: Vec<f64>, b: Vec<f64>,
                   m: usize, pool: &ThreadPool)
                   -> Arc<Mutex<Option<Matrix>>> {
    let m1: Arc<Mutex<Option<Matrix>>> = Arc::new(Mutex::new(None));
    let m1_clone = Arc::clone(&m1);

    pool.execute(move|| {
        // Use non-parallel algorithm once we're in a working thread
        let result = mult_strassen(
            &mut Matrix::with_vector(a, m, m),
            &mut Matrix::with_vector(b, m, m)
        );

        *m1_clone.lock().unwrap() = Some(result);
    });

    return m1;
}