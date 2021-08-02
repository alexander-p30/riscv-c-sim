#ifndef RISCV_MEMORY_H
#define RISCV_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 4096

int32_t lw(uint32_t address, int32_t kte);

int32_t lb(uint32_t address, int32_t kte);

int32_t lbu(uint32_t address, int32_t kte);

void sw(uint32_t address, int32_t kte, int32_t dado);

void sb(uint32_t address, int32_t kte, int8_t dado);

int32_t* getMem();

void resetMem();

#endif
