#include <stdio.h>
#include <string.h>
#include "../include/cpu.h"

void cpu_init(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
    cpu->sp = RAM_SIZE - 1; // Start stack at top of memory
    // printf("%lu\n", sizeof(CPU));
}

void cpu_load_program(CPU *cpu, const uint8_t *program, size_t size) {
    if (size > RAM_SIZE) {
        fprintf(stderr, "Program too large for RAM\n");
        return;
    }

    // Copy program bytes into beginning of RAM
    memcpy(cpu->ram, program, size);
}

uint8_t cpu_fetch(CPU *cpu) {
    return cpu->ram[cpu->pc++];
}

void push(CPU *cpu, uint8_t value) {
    if (cpu->sp == 0) {
        fprintf(stderr, "Stack overflow\n");
        cpu->halted = 1;
        return;
    }
    cpu->ram[cpu->sp--] = value;
}

uint8_t pop(CPU *cpu) {
    if (cpu->sp == RAM_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        cpu->halted = 1;
        return 0;
    }

    return cpu->ram[++cpu->sp];
}

/*
Performs one full fetch-decode-execute cycle
1. Fetch next instruction (opcode) from RAM at the program counter
2. Decode which instruction it is
3. Perform the instructions behavior
*/
void cpu_step(CPU *cpu) {
    // Fetch next opcode 
    uint8_t opcode = cpu_fetch(cpu);

    // Decode instruction
    switch (opcode) {
        case OP_LOAD: {
            // Load Rx value
            uint8_t reg = cpu_fetch(cpu); // e.g. 0 for R0
            uint8_t val = cpu_fetch(cpu); // e.g. 5

            if (reg < NUM_REGISTERS) {
                cpu->registers[reg] = val; // R[reg] = val
                printf("LOAD R%d <- %d\n", reg, val);
            } else {
                fprintf(stderr, "Invalid Register: R%d\n", reg);
            }

            break;
        }

        case OP_ADD: {
            uint8_t reg_dest = cpu_fetch(cpu);
            uint8_t reg_src = cpu_fetch(cpu);

            if (reg_dest < NUM_REGISTERS && reg_src < NUM_REGISTERS) {
                uint8_t val_dest = cpu->registers[reg_dest];
                uint8_t val_src = cpu->registers[reg_src];
                uint8_t sum = val_dest + val_src;

                cpu->registers[reg_dest] = sum;

                printf("ADD R%d <- R%d (%d + %d = %d)\n", reg_dest, reg_src, val_dest, val_src, sum);
            } else {
                fprintf(stderr, "Invalid Register: R%d or R%d\n", reg_dest, reg_src);
                cpu->halted = 1;
            }

            break;
        }

        case OP_CMP: {
            uint8_t reg_x = cpu_fetch(cpu);
            uint8_t reg_y = cpu_fetch(cpu);

            if (reg_x < NUM_REGISTERS && reg_y < NUM_REGISTERS) {
                uint8_t val_x = cpu->registers[reg_x];
                uint8_t val_y = cpu->registers[reg_y];
                cpu->flag_zero = (val_x == val_y) ? 1 : 0;
                printf("CMP R%d (%d) == R%d (%d) -> flag_zero = %d\n", reg_x, val_x,
                reg_y, val_y, cpu->flag_zero);
            } else {
                fprintf(stderr, "Invalid Register: R%d or R%d\n", reg_x, reg_y);
            }

            break;
        }

        case OP_JE: {
            uint8_t addr = cpu_fetch(cpu);
            if (cpu->flag_zero) {
                printf("JE to 0x%02X (flag_zero = 1)\n", addr);
                cpu->pc = addr;
            } else {
                printf("JE skipped (flag_zero = 0)\n");
            }

            break;
        }

        case OP_JMP: {
            uint8_t addr = cpu_fetch(cpu);
            printf("JMP to 0x%02X\n", addr);
            cpu->pc = addr;
            break;
        }

        case OP_CALL: {
            uint8_t addr = cpu_fetch(cpu);
            // Push current pc onto the stack
            push(cpu, cpu->pc);

            // Jump to the function address
            cpu->pc = addr;

            printf("CALL 0x%02X (return to 0x%02X)", addr, cpu->pc);
            break;
        }

        case OP_RET: {
            uint8_t ret_addr = cpu_fetch(cpu);
            cpu->pc = ret_addr;
            printf("RET to 0x%02X\n", ret_addr);
            break;
        }

        case OP_HALT: {
            cpu->halted = 1; // Set halted flag
            printf("HALT\n");
            break;
        }

        default:
            fprintf(stderr, "Unknown opcode: 0x%02X\n", opcode);
            cpu->halted = 1;
            break;
    }
}