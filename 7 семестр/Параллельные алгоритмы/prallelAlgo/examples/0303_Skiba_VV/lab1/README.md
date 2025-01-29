## Installing rust toolchain is easy!
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```


## To run different versions of this program:
- Processes version:
```bash
cargo run --release --bin processes
```

- Threads version:
```bash
cargo run --release --bin threads
```

- Threads optimized version:
```bash
cargo run --release --bin threads-optimized
```


