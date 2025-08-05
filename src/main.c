#include <stdio.h>
#include "../include/cpu.h"

int main() {
    CPU cpu;
    cpu_init(&cpu);

    cpu_load_program(&cpu, "bin/program.bin");

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