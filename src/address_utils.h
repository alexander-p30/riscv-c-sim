#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include "riscv_memory.h"

#define ADDRESS_STEP 4

int validateWordAddress(int32_t address);

int validateByteAddress(int32_t address);

#endif
