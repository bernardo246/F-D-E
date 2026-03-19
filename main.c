#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0;
uint8_t zf = 0;
uint8_t running = 1;
int ciclo = 0;

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc];
    *a = mem[pc + 1];
    *b = mem[pc + 2];
    pc += 3;
}

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
        default:
            printf("Erro: opcode invalido %u\n", op);
            running = 0;
            break;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nome = "???";

    switch (op) {
        case 0x01: nome = "LOAD"; break;
        case 0x02: nome = "STORE"; break;
        case 0x03: nome = "ADD"; break;
        case 0x04: nome = "SUB"; break;
        case 0x05: nome = "MOV"; break;
        case 0x06: nome = "CMP"; break;
        case 0x07: nome = "JMP"; break;
        case 0x08: nome = "JZ"; break;
        case 0x09: nome = "JNZ"; break;
        case 0x0A: nome = "HALT"; break;
    }

    printf("Ciclo %d: %-5s %3d,%3d | R0=%3d R1=%3d R2=%3d R3=%3d | PC=%3d ZF=%d\n",
           ciclo, nome, a, b,
           reg[0], reg[1], reg[2], reg[3], pc, zf);
}

int main() {
    // Dados do array
    mem[0x10] = 3;
    mem[0x11] = 7;
    mem[0x12] = 2;
    mem[0x13] = 5;
    mem[0x14] = 1;
    mem[0x15] = 8;
    mem[0x16] = 4;
    mem[0x17] = 6;

    // Programa começa em 0x30
    pc = 0x30;

    mem[0x30] = 0x05; mem[0x31] = 0x00; mem[0x32] = 0x00; // MOV R0, 0

    mem[0x33] = 0x01; mem[0x34] = 0x01; mem[0x35] = 0x10; // LOAD R1, 0x10
    mem[0x36] = 0x03; mem[0x37] = 0x00; mem[0x38] = 0x01; // ADD R0, R1

    mem[0x39] = 0x01; mem[0x3A] = 0x01; mem[0x3B] = 0x11; // LOAD R1, 0x11
    mem[0x3C] = 0x03; mem[0x3D] = 0x00; mem[0x3E] = 0x01; // ADD R0, R1

    mem[0x3F] = 0x01; mem[0x40] = 0x01; mem[0x41] = 0x12; // LOAD R1, 0x12
    mem[0x42] = 0x03; mem[0x43] = 0x00; mem[0x44] = 0x01; // ADD R0, R1

    mem[0x45] = 0x01; mem[0x46] = 0x01; mem[0x47] = 0x13; // LOAD R1, 0x13
    mem[0x48] = 0x03; mem[0x49] = 0x00; mem[0x4A] = 0x01; // ADD R0, R1

    mem[0x4B] = 0x01; mem[0x4C] = 0x01; mem[0x4D] = 0x14; // LOAD R1, 0x14
    mem[0x4E] = 0x03; mem[0x4F] = 0x00; mem[0x50] = 0x01; // ADD R0, R1

    mem[0x51] = 0x01; mem[0x52] = 0x01; mem[0x53] = 0x15; // LOAD R1, 0x15
    mem[0x54] = 0x03; mem[0x55] = 0x00; mem[0x56] = 0x01; // ADD R0, R1

    mem[0x57] = 0x01; mem[0x58] = 0x01; mem[0x59] = 0x16; // LOAD R1, 0x16
    mem[0x5A] = 0x03; mem[0x5B] = 0x00; mem[0x5C] = 0x01; // ADD R0, R1

    mem[0x5D] = 0x01; mem[0x5E] = 0x01; mem[0x5F] = 0x17; // LOAD R1, 0x17
    mem[0x60] = 0x03; mem[0x61] = 0x00; mem[0x62] = 0x01; // ADD R0, R1

    mem[0x63] = 0x02; mem[0x64] = 0x00; mem[0x65] = 0x20; // STORE R0, 0x20
    mem[0x66] = 0x0A; mem[0x67] = 0x00; mem[0x68] = 0x00; // HALT

    while (running && pc < 256) {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }

    printf("\nResultado final armazenado em mem[0x20] = %d\n", mem[0x20]);

    if (mem[0x20] == 36) {
        printf("Validacao correta: soma = 36\n");
    } else {
        printf("Validacao incorreta: esperado = 36\n");
    }

    return 0;
}