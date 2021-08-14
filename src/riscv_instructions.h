#ifndef RISCV_INSTRUCTIONS_H
#define RISCV_INSTRUCTIONS_H

#include <stdint.h>
#include <stdio.h>

#define OPCODE_U_0 0x37
#define OPCODE_U_1 0x17
#define OPCODE_I_0 0x3
#define OPCODE_I_1 0x13
#define OPCODE_I_2 0x73
#define OPCODE_I_3 0x67
#define OPCODE_R 0x33
#define OPCODE_S 0x23
#define OPCODE_B 0x63
#define OPCODE_J 0x6F

#define OPCODE_SIZE 7
#define RD_SIZE 5
#define FUNCT3_SIZE 3
#define RS1_SIZE 5
#define RS2_SIZE 5

void fetch();

void decode();

void execute();
void execute_U();
void execute_I();
void execute_R();
void execute_S();
void execute_B();
void execute_J();

void step();

void run();

void dump_mem(int start, int end, char format);

void dump_reg(char format);

int32_t get_imm();

#endif
