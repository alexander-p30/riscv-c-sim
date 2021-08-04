#include <stdio.h>
#include "address_utils.h"

int validateWordAddress(int32_t address) {
  uint8_t isAddressPositive = address >= 0;
  uint8_t isAddressBelowMemSizeInWords = address <= MEM_SIZE_IN_BYTES - 4;
  uint8_t isAddressMultipleOfStep = address % ADDRESS_STEP == 0;

  return isAddressPositive && isAddressBelowMemSizeInWords && isAddressMultipleOfStep;
}

int validateByteAddress(int32_t address) {
  uint8_t isAddressPositive = address >= 0;
  uint8_t isAddressBelowMemSize = address <= MEM_SIZE_IN_BYTES - 1;

  return isAddressPositive && isAddressBelowMemSize;
}

