# 🧠 8-Bit Virtual CPU Emulator in C

This project is a simulated 8-bit CPU written in C. It mimics how a real processor fetches, decodes, and executes instructions using a custom instruction set, registers, memory, and a stack-based control flow.

---

## 🚀 Features

- **8 General-Purpose Registers** (`R0` to `R7`, 8-bit each)
- **256 Bytes of RAM**
- **Program Counter (PC)** and **Stack Pointer (SP)**
- **Flags** (currently: `zero` flag for comparisons)
- **Fetch–Decode–Execute Cycle**
- Custom **Instruction Set Architecture (ISA)**:
  - `LOAD Rx, val`
  - `ADD Rx, Ry`
  - `CMP Rx, Ry`
  - `JE addr` (jump if equal)
  - `JMP addr` (unconditional jump)
  - `CALL addr` / `RET`
  - `HALT`

---

## 🧱 How It Works

The emulator simulates a simplified CPU architecture:
- Instructions and data are stored in a single block of memory (`ram[256]`)
- The `cpu_step()` function fetches the next opcode from memory, decodes it, and performs the corresponding operation
- For control flow, it supports conditionals (`CMP`, `JE`) and subroutines (`CALL`, `RET`) using a manually managed stack

---

## 🧪 Example Program

```c
uint8_t program[] = {
    0x10, 0x00, 0x05,  // LOAD R0, 5
    0x10, 0x01, 0x05,  // LOAD R1, 5
    0x30, 0x00, 0x01,  // CMP R0, R1
    0x40, 0x0A,        // JE to 0x0A
    0xFF,              // HALT
    0x10, 0x02, 0x99,  // LOAD R2, 153
    0xFF               // HALT
};
