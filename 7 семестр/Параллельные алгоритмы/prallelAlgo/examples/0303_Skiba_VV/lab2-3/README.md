## Installing rust toolchain is easy!
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## To run all versions of queue:
```bash
cargo run --release --all-features -- [producers_c] [consumers_c] [matrix_size]
```

Arguments are optional, default values are: 40 100 50 you can skip some of them

If you want to run specific version of queue, add one or more features:
- my_blocking_queue: My implementation of blocking queue (with coarse-grained locking)
- my_lock_free_queue: My implementation of lock free queue (based on CAS operations)
- my_shared_queue: My implementation of shared queue (with fine-grained locking)
- crossbeam_queue: Crossbeam implementation of lock free queue
- async_channels_threads: Async channels with threads. This is mostly idiomatic to rust.

Also, you can use custom implementation of Mutex and Condvar from crate parking_lot:
- advanced_sync: This feature replaces std::sync::Mutex and std::sync::Condvar with parking_lot::Mutex and parking_lot::Condvar
It is said to be more efficient in most cases.

For example, to run blocking queue version on 4 producers, 2 consumers and 500x500 matrix size, run:
```bash
cargo run --release --features my_blocking_queue -- 4 2 500
```

If you want to use efficient mutex and condvar, run:
```bash
cargo run --release --features my_blocking_queue,advanced_sync -- 4 2 500
```