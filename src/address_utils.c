#include <stdio.h>
#include "address_utils.h"

int validateWordAddress(int32_t address) {
  uint8_t isAddressMultipleOfStep = address % ADDRESS_STEP == 0;

  return validateByteAddress(address) && isAddressMultipleOfStep;
}

int validateByteAddress(int32_t address) {
  uint8_t isAddressNatural = address >= 0;
  uint8_t isAddressInsideMemSize = address <= MEM_SIZE;

  return isAddressNatural && isAddressInsideMemSize;
}

int test(int32_t a) {
  if(validateWordAddress(a)) {
    printf("%d true\n", a);
  } else {
    printf("%d false\n", a);
  }

  return validateWordAddress(a);
}

