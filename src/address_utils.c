#include <stdio.h>
#include "address_utils.h"

int validateWordAddress(int32_t address) {
  uint8_t isAddressPositive = address >= 0;
  uint8_t isAddressBelowMemSizeInWords = address <= MEM_SIZE_IN_BYTES - 4;
  uint8_t isAddressMultipleOfStep = address % ADDRESS_STEP == 0;
  uint8_t isAddressValid = isAddressPositive && isAddressBelowMemSizeInWords && isAddressMultipleOfStep;

  if(!isAddressValid) {
    printf("O endereço de palavra %d fornecido é inválido! ", address);
    printf(
      "Endereços de palavra devem ser divisíveis por %d e menores ou iguais a %d.\n",
      ADDRESS_STEP, MEM_SIZE_IN_BYTES - 4
    );
  }

  return isAddressValid;
}

int validateByteAddress(int32_t address) {
  uint8_t isAddressPositive = address >= 0;
  uint8_t isAddressBelowMemSize = address <= MEM_SIZE_IN_BYTES - 1;
  uint8_t isAddressValid = isAddressPositive && isAddressBelowMemSize;

  if(!isAddressValid) {
    printf("O endereço de byte %d fornecido é inválido! ", address);
    printf(
      "Endereços de byte devem ser maiores ou iguais a 0 e menores ou iguais a %d\n",
      MEM_SIZE_IN_BYTES - 1
    );
  }

  return isAddressValid;
}

