#include <stdio.h>
#include "address_utils.h"
#include "binary_utils.h"

int32_t computeByteInIntExtractionMask(uint8_t byteIndexInInt) {
  int32_t mask = 0xFF << (byteIndexInInt * 8);

  return mask;
}

int32_t extractByteFromInt(int32_t fullInt, int32_t mask) {
  return mask & fullInt;
}

