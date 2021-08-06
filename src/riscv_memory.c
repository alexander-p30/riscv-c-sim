#include <stdio.h>
#include "address_utils.h"
#include "binary_utils.h"
#include "riscv_memory.h"

int32_t mem[MEM_SIZE_IN_WORDS];

int32_t lw(uint32_t address, int32_t kte) {
  int32_t tempAddress = address + kte;

  if(!validateWordAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser divisível por %d e menor ou igual a %d.\n", ADDRESS_STEP, MEM_SIZE_IN_BYTES - 4);
    return 0;
  }

  int32_t finalAddress = tempAddress / 4;

  return mem[finalAddress];
}

int32_t lb(uint32_t address, int32_t kte) {
  int32_t tempAddress = address + kte;

  if(!validateByteAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser maior ou igual a 0 e menor ou igual a %d\n", MEM_SIZE_IN_BYTES - 1);
    return 0;
  }

  uint8_t byteIndexInInt = tempAddress % ADDRESS_STEP;
  int32_t finalAddress = (tempAddress - byteIndexInInt) / 4;
  int32_t mask = computeByteInIntExtractionMask(byteIndexInInt);
  uint32_t shiftedByte = extractByteFromInt(mem[finalAddress], mask) >> (byteIndexInInt * 8);
  int32_t signedByte = shiftedByte;

  if(shiftedByte & 0b10000000)
    signedByte |= 0xFFFFFF00;

  return signedByte;
}

int32_t lbu(uint32_t address, int32_t kte) {
  int32_t tempAddress = address + kte;

  if(!validateByteAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser maior ou igual a 0 e menor ou igual a %d\n", MEM_SIZE_IN_BYTES - 1);
    return 0;
  }

  uint8_t byteIndexInInt = tempAddress % ADDRESS_STEP;
  int32_t finalAddress = (tempAddress - byteIndexInInt) / 4;
  int32_t mask = computeByteInIntExtractionMask(byteIndexInInt);
  int32_t shiftedByte = extractByteFromInt(mem[finalAddress], mask);

  return (int32_t)((uint32_t)shiftedByte >> (byteIndexInInt * 8));
}

void sw(uint32_t address, int32_t kte, int32_t dado) {
  int32_t tempAddress = address + kte;

  if(!validateWordAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser divisível por %d e menor ou igual a %d.\n", ADDRESS_STEP, MEM_SIZE_IN_BYTES - 4);
    return;
  }

  int32_t finalAddress = tempAddress / 4;
  mem[finalAddress] = dado;
  return;
}

void sb(uint32_t address, int32_t kte, int8_t dado) {
  int32_t tempAddress = address + kte;

  if(!validateByteAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser maior ou igual a 0 e menor ou igual a %d\n", MEM_SIZE_IN_BYTES - 1);
    return;
  }

  uint8_t byteIndexInInt = tempAddress % ADDRESS_STEP;
  int32_t finalAddress = tempAddress - byteIndexInInt;
  int32_t extendedValue = (dado << (byteIndexInInt * 8) & computeByteInIntExtractionMask(byteIndexInInt));
  uint32_t clearByteInPositionMask = ~computeByteInIntExtractionMask(byteIndexInInt);
  int32_t currentlyStoredWord = lw(finalAddress, 0);
  int32_t dataToBeStored = (currentlyStoredWord & clearByteInPositionMask) | extendedValue;
  sw(finalAddress, 0, dataToBeStored);
}

int32_t* getMem() {
  return mem;
}

void resetMem() {
  int i = 0;
  for(i = 0; i <= MEM_SIZE_IN_WORDS; i++) {
    mem[i] = 0;
  }
}

