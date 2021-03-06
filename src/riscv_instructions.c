#include "riscv_instructions.h"
#include "riscv_memory.h"

extern int32_t mem[MEM_SIZE_IN_WORDS];

// Condição de parada
int exitProg = 0;

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
int32_t funct3 = 0x0;
int32_t funct7  = 0x0;
int32_t shamt = 0x0;

int32_t imm12_i = 0x0;
int32_t imm12_s = 0x0;
int32_t imm13_b = 0x0;
int32_t imm20_u = 0x0;
int32_t imm21_j = 0x0;

enum Registers {
  ZERO = 0, RA = 1, SP = 2, GP = 3, TP = 4, T0 = 5,
  T1 = 6, T2 = 7, S0 = 8, S1 = 9, A0 = 10,
  A1 = 11, A2 = 12, A3 = 13, A4 = 14, A5 = 15, A6 = 16,
  A7 = 17, S2 = 18, S3 = 19, S4 = 20, S5 = 21, S6 = 22,
  S7 = 23, S8 = 24, S9 = 25, S10 = 26, S11 = 27, T3 = 28,
  T4 = 29, T5 = 30, T6 = 31
};

int32_t breg[32] = { };

void fetch() {
  ri = lw(pc, 0);
  pc = pc + 4;
}

void decode() {
  const int32_t opcode_mask = 0x7F;
  const int32_t rd_mask = 0x1F;
  const int32_t funct3_mask = 0x7;
  const int32_t rs1_mask = 0x1F;
  const int32_t rs2_mask = 0x1F;
  const int32_t shamt_mask = 0x1F;

  opcode = ri & opcode_mask;
  rs2 = (ri >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE)) & rs2_mask;
  rs1 = (ri >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE)) & rs1_mask;
  rd = (ri >> OPCODE_SIZE) & rd_mask;
  shamt = (ri >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE)) & shamt_mask;
  funct3 = (ri >> (OPCODE_SIZE + RD_SIZE)) & funct3_mask;
  funct7 = ri >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE + RS2_SIZE);

  imm12_i = get_imm();
  imm12_s = get_imm();
  imm13_b = get_imm();
  imm20_u = get_imm();
  imm21_j = get_imm();
}

int32_t get_imm() {
  const int32_t imm12_i_mask = 0xFFF00000;
  const int32_t imm12_s_mask = 0xFE000F80;
  const int32_t imm13_b_mask = 0xFE000F80;
  const int32_t imm20_u_mask = 0xFFFFF000;
  const int32_t imm21_j_mask = 0xFFFFF000;

  int32_t msb = 0x0;
  int32_t second_msb = 0x0;
  int32_t upper_part = 0x0;
  int32_t eleventh_bit = 0x0;
  int32_t lower_part = 0x0;

  switch(opcode) {
  case OPCODE_U_0:
    return ri & imm20_u_mask;
  case OPCODE_U_1:
    return ri & imm20_u_mask;
  case OPCODE_I_0:
    return (int32_t)(ri & imm12_i_mask) >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE);
  case OPCODE_I_1:
    return (int32_t)(ri & imm12_i_mask) >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE);
  case OPCODE_I_2:
    return (int32_t)(ri & imm12_i_mask) >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE);
  case OPCODE_I_3:
    return (int32_t)(ri & imm12_i_mask) >> (OPCODE_SIZE + RD_SIZE + FUNCT3_SIZE + RS1_SIZE);
  case OPCODE_S:
    upper_part = ((int32_t)(ri & 0xFE000000) >> (RS2_SIZE + RS1_SIZE + FUNCT3_SIZE + RD_SIZE + 2));
    lower_part = (ri & 0x00000F80) >> OPCODE_SIZE;
    return (upper_part | lower_part);
  case OPCODE_B:
    msb = (int32_t)(ri & 0x80000000) >> 31 - 12;
    second_msb = (ri & 0x00000080) << 4;
    upper_part = (ri & 0x7E000000) >> ((RS2_SIZE  + RS1_SIZE + FUNCT3_SIZE + RD_SIZE + OPCODE_SIZE) - 2 - 3);
    lower_part = (ri & 0xF00) >> OPCODE_SIZE;
    return (msb | second_msb | upper_part | lower_part);
  case OPCODE_J:
    msb = (int32_t)(ri & 0x80000000) >> 11;
    upper_part = (ri & 0x000FF000);
    eleventh_bit = (ri & 0x00100000) >> 9;
    lower_part = (ri & 0x7FE00000) >> 20;
    return (msb | upper_part | eleventh_bit | lower_part);
  }
}

void execute() {
  breg[ZERO] = 0;
  switch(opcode) {
    case OPCODE_U_0:
      execute_U();break;
    case OPCODE_U_1:
      execute_U();break;
    case OPCODE_I_0:
      execute_I();break;
    case OPCODE_I_1:
      execute_I();break;
    case OPCODE_I_2:
      execute_I();break;
    case OPCODE_I_3:
      execute_I();break;
    case OPCODE_R:
      execute_R();break;
    case OPCODE_S:
      execute_S();break;
    case OPCODE_B:
      execute_B();break;
    case OPCODE_J:
      execute_J();break;
    default:
      printf("Opcode 0x%8x inválido\n", opcode);break;
  }
}

void execute_U() {
  switch(opcode) {
    case OPCODE_U_0: // lui
     breg[rd] = imm20_u;break;
    case OPCODE_U_1: // auipc
     breg[rd] = pc + imm20_u - 4;break;
  }
}

void execute_I() {
  switch(opcode) {
    case OPCODE_I_0:
      switch(funct3) {
        case 0b000: // lb
          breg[rd] = lb(breg[rs1], imm12_i);break;
        case 0b010: // lw
          breg[rd] = lw(breg[rs1], imm12_i);break;
        case 0b100: // lbu
          breg[rd] = lbu(breg[rs1], imm12_i);break;
      } break;
    case OPCODE_I_1:
      switch(funct3) {
        case 0b000: // addi
          breg[rd] = breg[rs1] + imm12_i;break;
        case 0b110: // ori
          breg[rd] = breg[rs1] | imm12_i;break;
        case 0b111: // andi
          breg[rd] = breg[rs1] & imm12_i;break;
        case 0b001: // slli
          breg[rd] = breg[rs1] << imm12_i;break;
        case 0b101:
          switch(funct7) {
            case 0b0000000: // srli
              breg[rd] = (uint32_t)breg[rs1] >> imm12_i;break;
            case 0b0100000: // srai
              breg[rd] = breg[rs1] >> imm12_i;break;
          } break;
      } break;
    case OPCODE_I_2:
      switch(breg[A7]) {
        case 1: // printInt
          printf(" %d", breg[A0]);break;
        case 4: // printString
          uint32_t character = (uint32_t)breg[A0];
          while(lb(character,0)) {
            printf("%c", (char)lb(character,0));
            character++;
          } break;
        case 10: // exit
          exitProg = 1;break;
      } break;
    case OPCODE_I_3: // jalr
      breg[rd] = pc;
      pc = breg[rs1] + imm12_i;
      breg[ZERO] = 0;
      break;
  }
}

void execute_R() {
  switch(funct3) {
    case 0b000:
      switch(funct7) {
        case 0b00000000: // add
          breg[rd] = breg[rs1] + breg[rs2];break;
        case 0b0100000: // sub
          breg[rd] = breg[rs1] - breg[rs2];break;
      } break;
    case 0b010: // slt
      breg[rd] = breg[rs1] < breg[rs2];break;
    case 0b011: //sltu
      breg[rd] = ((uint32_t)breg[rs1] < (uint32_t)breg[rs2]);break;
    case 0b100: // xor
      breg[rd] = breg[rs1] ^ breg[rs2];break;
    case 0b110: // or
      breg[rd] = breg[rs1] | breg[rs2];break;
    case 0b111: // and
      breg[rd] = breg[rs1] & breg[rs2];break;
  }
}

void execute_S() {
  switch(funct3) {
    case 0b000: // sb
      sb(breg[rs1], imm12_s, (int8_t)breg[rs2]); break;
    case 0b010: // sw
      sw(breg[rs1], imm12_s, breg[rs2]); break;
  }
}

void execute_B() {
  switch(funct3) {
    case 0b000: // beq
      if(breg[rs1] == breg[rs2]) {
        pc += imm13_b - 4;
      } break;
    case 0b001: // bne
      if(breg[rs1] != breg[rs2]) {
        pc += imm13_b - 4;
      } break;
    case 0b100: // blt
      if(breg[rs1] < breg[rs2]) {
        pc += imm13_b - 4;
      } break;
    case 0b101: // bge
      if(breg[rs1] >= breg[rs2]) {
        pc += imm13_b - 4;
      } break;
    case 0b110: // bltu
      if(((uint32_t)breg[rs1]) < ((uint32_t)breg[rs2])) {
        pc += imm13_b - 4;
      } break;
    case 0b111: // bgeu
      if(((uint32_t)breg[rs1]) >= ((uint32_t)breg[rs2])) {
        pc += imm13_b - 4;
      } break;
  }
}

void execute_J() { // jal
  breg[rd] = pc;
  pc += imm21_j - 4;
  breg[ZERO] = 0;
}

void step() {
  fetch();
  decode();
  execute();
}

void dump_mem(int start, int end, char format) {
  int i = 0;
  switch(format) {
    case 'd':
      for(i = start; i <= end; i++)
        printf("%d\n", mem[i]);
      break;
    case 'h':
      for(i = start; i <= end; i++)
        printf("%x\n", mem[i]);
      break;
  }
}

void dump_reg(char format) {
  int i = 0;
  switch(format) {
    case 'd':
      for(i = 0; i < 32; i++)
        printf("%d:\t%8d\n", i, breg[i]);
      break;
    case 'h':
      for(i = 0; i < 32; i++)
        printf("%x\n", breg[i]);
      break;
  }
  printf("\n");
}

void run() {
  pc = 0; ri = 0;
  exitProg = 0;
  sp = 0x3ffc;
  gp = 0x1800;

	while (!exitProg && (pc < 0x2000)) {
    step();
  }
}

void load_mem(const char *fileName, int start) {
	int *memPtr = mem + (start >> 2);
	FILE *file;
  file = fopen(fileName, "rb");

	if (!file) {
		printf("Arquivo inválido!\n");
	} else {
		while (!feof(file)) {
			fread(memPtr, 4, 1, file);
			memPtr++;
		}
		fclose(file);
	}
}

