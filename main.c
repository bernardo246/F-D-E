#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};  // memória principal com 256 posições, iniciada em 0
uint8_t reg[4] = {0};    // 4 registradores (R0, R1, R2, R3), iniciados em 0
uint8_t pc = 0;          // Program Counter: aponta para a próxima instrução
uint8_t zf = 0;          // Zero Flag: vira 1 quando uma comparação é igual
uint8_t running = 1;     // controle do loop: 0 = parar, 1 = continuar
int ciclo = 0;           // contador de ciclos executados

// busca 3 bytes da memória: opcode, operando A e operando B
void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc]; *a = mem[pc+1]; *b = mem[pc+2];
    pc += 3;
}

// decodifica o opcode e executa a instrução correspondente
void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case 0x01: reg[a] = mem[b]; break;
        case 0x02: mem[b] = reg[a]; break;
        case 0x03: reg[a] = reg[a] + reg[b]; break;
        case 0x04: reg[a] = reg[a] - reg[b]; break;
        case 0x05: reg[a] = b; break;
        case 0x06: zf = (reg[a] == reg[b]) ? 1 : 0; break;
        case 0x07: pc = a; break;
        case 0x08: if (zf) pc = a; break;
        case 0x09: if (!zf) pc = a; break;
        case 0x0A: running = 0; break;
    }
}

// imprime o estado do processador após cada instrução (trace de execução)
void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nomes[] = {"","LOAD","STORE","ADD",
        "SUB","MOV","CMP","JMP","JZ","JNZ","HALT"};
    printf("Ciclo %d: %-5s %d,%d | R0=%3d R1=%3d"
           " R2=%3d R3=%3d | PC=%3d ZF=%d\n",
           ciclo, nomes[op], a, b,
           reg[0], reg[1], reg[2], reg[3], pc, zf);
}

int main() {
    mem[50] = 10;   // array[0]
    mem[51] = 20;   // array[1]
    mem[52] = 30;   // array[2]

    mem[0] = 0x05; mem[1] = 0; mem[2] = 0;
    mem[3] = 0x01; mem[4] = 1; mem[5] = 50;
    mem[6] = 0x03; mem[7] = 0; mem[8] = 1;
    mem[9]  = 0x01; mem[10] = 1; mem[11] = 51;
    mem[12] = 0x03; mem[13] = 0; mem[14] = 1;
    mem[15] = 0x01; mem[16] = 1; mem[17] = 52;
    mem[18] = 0x03; mem[19] = 0; mem[20] = 1;
    mem[21] = 0x0A; mem[22] = 0; mem[23] = 0;
    

    while (running && pc < 256) {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }

    printf("\n seu resultado: R0 = %d\n", reg[0]);
    return 0;
}