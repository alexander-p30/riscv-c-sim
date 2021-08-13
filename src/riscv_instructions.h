#ifndef RISCV_INSTRUCTIONS_H
#define RISCV_INSTRUCTIONS_H

#include <stdint.h>

void fetch();

void decode();

void execute();

void step();

void run();

void dump_mem(int start, int end, char format);

void dump_reg(char format);

#endif
