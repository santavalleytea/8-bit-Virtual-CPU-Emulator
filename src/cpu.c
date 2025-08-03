#include <stdio.h>
#include <string.h>
#include "../include/cpu.h"

void cpu_init(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
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

            if (reg_dest < NUM_REGISTERS) {
                uint8_t sum = cpu->registers[reg_dest] + cpu->registers[reg_src];
                cpu->registers[reg_dest] = sum;
                printf("ADD R%d <- R%d (%d + %d = %d)\n", reg_dest, reg_src, 
                cpu->registers[reg_dest], cpu->registers[reg_src], sum);
            } else {
                fprintf(stderr, "Invalid Register: R%d or R%d\n", reg_dest, reg_src);
                cpu->halted = 1;
            }

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