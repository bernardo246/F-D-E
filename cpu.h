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

extern int memory[MEM_SIZE]; //uma memoria global

void inicializar(CPU *cpu);
void rodar_programa();
int  fetch(CPU *cpu);
void decode_execute(CPU *cpu, int instruction); //recebe uma instrução em formato numérico e descobre o que fazer com ela.
void run(CPU *cpu); // Ela fica rodando o ciclo do processador até o programa terminar.


#endif
