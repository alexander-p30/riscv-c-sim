#include <stdio.h>
#include "address_utils.h"

int validateWordAddress(int32_t address) {
  uint8_t isAddressMultipleOfStep = address % ADDRESS_STEP == 0;

  return validateByteAddress(address) && isAddressMultipleOfStep;
}

int validateByteAddress(int32_t address) {
  uint8_t isAddressPositive = address >= 0;
  uint8_t isAddressInsideMemSize = address <= MEM_SIZE_IN_BYTES;

  return isAddressPositive && isAddressInsideMemSize;
}

