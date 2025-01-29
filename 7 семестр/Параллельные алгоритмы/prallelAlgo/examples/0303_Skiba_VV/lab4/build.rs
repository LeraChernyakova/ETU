// build.rs
fn main() {
    // panic if none of features are selected
    if !cfg!(feature = "multithreaded") && !cfg!(feature = "strassen") {
        panic!("At least one of features must be selected: multithreaded, strassen\nTry: cargo run --features multithreaded");
    }
}