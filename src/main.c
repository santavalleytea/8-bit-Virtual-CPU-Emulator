#include <stdio.h>
#include "../include/cpu.h"

int main() {
    CPU cpu;
    cpu_init(&cpu);

    uint8_t program[] = {
        0x10, 0x00, 0x05, // LOAD R0, 5
        0x10, 0x01, 0x09, // LOAD R1, 9
        0x20, 0x00, 0x01, // ADD R0 + R1
        0xFF              // HALT
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