#include <stdio.h>
#include "address_utils.h"
#include "binary_utils.h"

int32_t computeByteInIntExtractionMask(uint8_t byteIndexInInt) {
  int32_t mask = 0b11111111;
  uint8_t i = 0;

  for(i = 0; i < byteIndexInInt; i++) {
    mask <<= 8;
  }

  return mask;
}

int32_t extractByteFromInt(int32_t fullInt, int32_t mask) {
  return mask & fullInt;
}

