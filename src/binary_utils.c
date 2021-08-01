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

/* int main() { */
/*   printf("%d\n", computeByteInIntExtractionMask(0)); */
/*   printf("%d\n", extractByteFromInt(113, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(39, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(1, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(3, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", computeByteInIntExtractionMask(1)); */
/*   printf("%d\n", extractByteFromInt(65280, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(65280, computeByteInIntExtractionMask(1))); */
/*   printf("%d\n", extractByteFromInt(65280, computeByteInIntExtractionMask(2))); */
/*   printf("%d\n", extractByteFromInt(65280, computeByteInIntExtractionMask(3))); */
/*   printf("%d\n", computeByteInIntExtractionMask(2)); */
/*   printf("%d\n", extractByteFromInt(16711680, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(16711680, computeByteInIntExtractionMask(1))); */
/*   printf("%d\n", extractByteFromInt(16711680, computeByteInIntExtractionMask(2))); */
/*   printf("%d\n", extractByteFromInt(16711680, computeByteInIntExtractionMask(3))); */
/*   printf("%d\n", computeByteInIntExtractionMask(3)); */
/*   printf("%d\n", extractByteFromInt(-16777216, computeByteInIntExtractionMask(0))); */
/*   printf("%d\n", extractByteFromInt(-16777216, computeByteInIntExtractionMask(1))); */
/*   printf("%d\n", extractByteFromInt(-16777216, computeByteInIntExtractionMask(2))); */
/*   printf("%d\n", extractByteFromInt(-16777216, computeByteInIntExtractionMask(3))); */
/* } */

