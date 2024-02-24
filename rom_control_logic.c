#include <stdio.h>
#include <stdlib.h>

// Sinais de saída da lógica de controle
#define HLT 0b1000000000000000  // Halt clock
#define MI  0b0100000000000000  // Memory address register in
#define RI  0b0010000000000000  // RAM data in
#define RO  0b0001000000000000  // RAM data out
#define IO  0b0000100000000000  // Instruction register out
#define II  0b0000010000000000  // Instruction register in
#define AI  0b0000001000000000  // A register in
#define AO  0b0000000100000000  // A register out
#define EO  0b0000000010000000  // ALU out
#define SU  0b0000000001000000  // ALU subtract
#define BI  0b0000000000100000  // B register in
#define OI  0b0000000000010000  // Output register in
#define CE  0b0000000000001000  // Program counter enable
#define CO  0b0000000000000100  // Program counter out
#define J   0b0000000000000010  // Jump (program counter in)
#define FI  0b0000000000000001  // Flags in

// Micro instruções de cada step de uma instrução 
int microInstrucoes[16][8] = {
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0000 - NOP
  { MI|CO,  RO|II|CE,  IO|MI,  RO|AI,  0,           0, 0, 0 },   // 0001 - LDA
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|FI,    0, 0, 0 },   // 0010 - ADD
  { MI|CO,  RO|II|CE,  IO|MI,  RO|BI,  EO|AI|SU|FI, 0, 0, 0 },   // 0011 - SUB
  { MI|CO,  RO|II|CE,  IO|MI,  AO|RI,  0,           0, 0, 0 },   // 0100 - STA
  { MI|CO,  RO|II|CE,  IO|AI,  0,      0,           0, 0, 0 },   // 0101 - LDI
  { MI|CO,  RO|II|CE,  IO|J,   0,      0,           0, 0, 0 },   // 0110 - JMP
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 0111 - JC
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1000 - JZ
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1001 
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1010
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1011
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1100
  { MI|CO,  RO|II|CE,  0,      0,      0,           0, 0, 0 },   // 1101
  { MI|CO,  RO|II|CE,  AO|OI,  0,      0,           0, 0, 0 },   // 1110 - OUT
  { MI|CO,  RO|II|CE,  HLT,    0,      0,           0, 0, 0 },   // 1111 - HLT
};


int main() {
    
    int instrucao, step;
    
    FILE *arquivo;
    arquivo = fopen("controlLogicRom.txt", "w");

    if (arquivo == NULL) {
        printf("Houve um erro ao tentar gerar os arquivos.\n");
        system("pause");
        exit(1);
    }
    
    // Preenche as primeiras 128 posições de 00000000000 a 00001111111 
    for(instrucao = 0; instrucao < 16; instrucao++) {
        for(step = 0; step < 8; step++) {
            fprintf(arquivo, "%X\n", microInstrucoes[instrucao][step]);
        }
    } 

    // As próximas 128 posições possuem Carry Flag ativado
    microInstrucoes[7][2] = IO|J;
    // Preenche as próximas 128 posições de 00010000000 a 00011111111 
    for(instrucao = 0; instrucao < 16; instrucao++) {
        for(int step = 0; step < 8; step++) {
            fprintf(arquivo, "%X\n", microInstrucoes[instrucao][step]);
        }
    }

    // As próximas 128 posições possuem Zero Flag ativado e Carry Flag desativado
    microInstrucoes[7][2] = 0;
    microInstrucoes[8][2] = IO|J;
    // Preenche as próximas 128 posições de 00100000000 a 00101111111
    for(instrucao = 0; instrucao < 16; instrucao++) {
        for(int step = 0; step < 8; step++) {
            fprintf(arquivo, "%X\n", microInstrucoes[instrucao][step]);
        }
    }

    // As próximas 128 posições possuem Zero Flag ativado e Carry Flag ativado
    microInstrucoes[7][2] = IO|J;
    // Preenche as próximas 128 posições de 00110000000 a 00111111111
    for(instrucao = 0; instrucao < 16; instrucao++) {
        for(int step = 0; step < 8; step++) {
            fprintf(arquivo, "%X\n", microInstrucoes[instrucao][step]);
        }
    }

    fclose(arquivo);
    printf("Arquivos gerados com sucesso!.\n");

    return 0;
}
