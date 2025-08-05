#include <stdio.h>
#include "../include/cpu.h"

int main() {
    CPU cpu;
    cpu_init(&cpu);

    uint8_t program[] = {
        0x10, 0x00, 0x2A,   // LOAD R0, 42
        0x60, 0x00,         // PUSH R0
        0x10, 0x00, 0x00,   // LOAD R0, 0 (overwrite)
        0x61, 0x01,         // POP R1 (restore into R1)
        0xFF                // HALT
    };

    cpu_load_program(&cpu, program, sizeof(program));

    printf("== Running CPU ==\n");

    while(!cpu.halted) {
        cpu_step(&cpu);
    }

    printf("\n==Final Register Valus==\n");
    for (int i = 0; i < NUM_REGISTERS; ++i) {
        printf("R%d: %d\n", i, cpu.registers[i]);
    }

    return 0;
}