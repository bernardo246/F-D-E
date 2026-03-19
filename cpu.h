#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 256
#define NUM_REGS 8

typedef struct {
    int regs[8];   // Registradores R0–R7
    int pc;        // Program Counter
    int zero_flag; // Flag de zero
    int running;   // Controle do loop
} CPU;
