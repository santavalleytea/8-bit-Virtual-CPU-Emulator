#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define RAM_SIZE 256
#define NUM_REGISTERS 8
#define OP_LOAD 0x10
#define OP_ADD 0x20
#define OP_HALT 0xFF
#define OP_CMP 0x30
#define OP_JE 0x40
#define OP_JMP 0x41
#define OP_CALL 0x50
#define OP_RET 0x51

typedef struct {
    uint8_t registers[NUM_REGISTERS];   // R0 to R7
    uint8_t ram[RAM_SIZE];              // 256 bytes of RAM
    uint8_t pc;                         // 8 bit Program counter
    uint8_t sp;                         // 8 bit Stack pointer
    uint8_t flag_zero;                  // Zero flag for comparisons
    uint8_t halted;                     // Check whether cpu halted
} CPU;

// Initialize CPU, clear everything to 0
void cpu_init(CPU *cpu);

// Loads a program (array of bytes) into RAM
void cpu_load_program(CPU *cpu, const uint8_t *program, size_t size);

// Fetches next instruction and updates PC  
uint8_t cpu_fetch(CPU *cpu);

// Performs one full fetch-decode-execute cycle
void cpu_step(CPU *cpu);

// Stack operations
void push(CPU *cpu, uint8_t value);
uint8_t pop(CPU *cpu);


#endif