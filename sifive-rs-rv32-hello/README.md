
For the HiFive1 RevB (with onboard J-Link) run:

```sh
/path/to/JLinkGDBServer -device FE310 -if JTAG -speed 4000 -port 3333 -nogui
```

Then ask OpenOCD to program it:

```sh
./sciprts/upload --elf target/riscv32imac-unknown-none-elf/release/rv32-hifive-helloworld --openocd openocd --gdb /opt/riscv/bin/riscv64-unknown-elf-gdb  --openocd-config openocd.cfg
```

```sh
./scripts/upload --elf target/riscv32imac-unknown-none-elf/debug/rv32-hifive-helloworld --openocd openocd --gdb /opt/riscv/bin/riscv64-unknown-elf-gdb  --openocd-config openocd.cfg
```

Alternatively, `cargo run` apparently works.
