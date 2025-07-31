#include <stdio.h>
#include "../include/cpu.h"

int main() {
    CPU cpu;
    cpu_init(&cpu);

    uint8_t program[] = {
        0x10, 0x00, 0x05,
        0x20, 0x00, 0x00,
        0xFF
    };

    cpu_load_program(&cpu, program, sizeof(program));

    printf("== FETCHING INSTRUCTIONS ==\n");

    while(!cpu.halted && cpu.pc < sizeof(program)) {
        // Fetch next opcode
        uint8_t opcode = cpu_fetch(&cpu);

        // opcode in hex format
        printf("Fetched opcode: 0x%02X\n", opcode);
    }

    return 0;
}