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