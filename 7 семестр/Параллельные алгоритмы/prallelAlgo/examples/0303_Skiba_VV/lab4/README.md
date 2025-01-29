## Installing rust toolchain is easy!
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## To run multithreaded version of matrix multiplication:
```bash
cargo run --release --features multithreaded
```

## To run Strassen optimized version of matric multiplication:
```bash
cargo run --release --features strassen
```