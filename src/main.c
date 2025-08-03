#include <stdio.h>
#include "../include/cpu.h"

int main() {
    CPU cpu;
    cpu_init(&cpu);

    uint8_t program[] = {
        0x10, 0x00, 0x05, // LOAD R0, x
        0x10, 0x01, 0x05, // LOAD R1, y
        0x30, 0x00, 0x01,
        0x40, 0x0A,
        0xFF,              // HALT
        0x10, 0x02, 0x99,
        0xFF
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