#include "riscv_instructions.h"
#include "riscv_memory.h"

extern int32_t mem[MEM_SIZE_IN_WORDS];

// Registradores
uint32_t pc = 0x00000000;
uint32_t ri = 0x00000000;
uint32_t sp = 0x00003ffc;
uint32_t gp = 0x00001800;

// Campos de instrução
int32_t opcode = 0x0;
int32_t rs1 = 0x0;
int32_t rs2 = 0x0;
int32_t rd = 0x0;
int32_t shamt = 0x0;
int32_t funct3 = 0x0;
int32_t funct7  = 0x0;

enum Registers {
  ZERO = 0, RA = 1, SP = 2, GP = 3, TP = 4, T0 = 5,
  T1 = 6, T2 = 6, S0 = 8, FP = 8, S1 = 9, A0 = 10,
  A1 = 11, A2 = 12, A3 = 13, A4 = 14, A5 = 15, A6 = 16,
  A7 = 17, S2 = 18, S3 = 19, S4 = 20, S5 = 21, S6 = 22,
  S7 = 23, S8 = 24, S9 = 25, S10 = 26, S11 = 27, T3 = 28,
  T4 = 29, T5 = 30, T6 = 31
};

int32_t breg[32] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0
};

void fetch() {
  ri = lw(pc, 0);
  pc = pc + 4;
}

void decode() {
  const int32_t opcode_mask = 0x7F;
  const int32_t rd_mask = 0xF80;
  const int32_t funct3_mask = 0x7000;
  const int32_t rs1_mask = 0xF8000;
  const int32_t rs2_mask = 0x1F00000;
  const int32_t funct7_mask = 0xFE000000;
  const int32_t imm12_i_mask = 0xFFF00000;
  const int32_t imm12_s_mask = 0xFE000F80;
  const int32_t imm13 = 0xFE000F80;
  const int32_t imm20_u_mask = 0xFFFFF000;
  const int32_t imm21 = 0xFFFFF000;

  opcode = ri & opcode_mask;
  rd = ri & rd_mask;
  funct3 = ri & funct3_mask;
  funct7 = ri & funct7_mask;
  rs1 = ri & rs1_mask;
  rs2 = ri & rs2_mask;
}

