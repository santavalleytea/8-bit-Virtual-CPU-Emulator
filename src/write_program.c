#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t program[] = {
        0x10, 0x00, 0x05,  // LOAD R0, 5
        0x10, 0x01, 0x09,  // LOAD R1, 9
        0x20, 0x00, 0x01,  // ADD R0, R1
        0xFF               // HALT
    };

    FILE *f = fopen("bin/program.bin", "wb");
    if (!f) {
        perror("Could not create program.bin");
        return 1;
    }

    fwrite(program, 1, sizeof(program), f);
    fclose(f);

    printf("program.bin generated with %zu bytes.\n", sizeof(program));
    return 0;
}
