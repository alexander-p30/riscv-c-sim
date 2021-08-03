#include <stdio.h>
#include "address_utils.h"
#include "binary_utils.h"
#include "riscv_memory.h"

int32_t mem[MEM_SIZE];

int32_t lw(uint32_t address, int32_t kte) {
  int32_t tempAddress = address + kte;

  if(!validateWordAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser divisível por %d e menor ou igual a %d.\n", ADDRESS_STEP, MEM_SIZE);
    return 0;
  }

  int32_t finalAddress = tempAddress / 4;

  return mem[finalAddress];
}

int32_t lb(uint32_t address, int32_t kte) {
  int32_t finalAddress = address + kte;

  if(!validateByteAddress(finalAddress)) {
    printf("O endereço %d fornecido é inválido! ", finalAddress);
    printf("O endereço deve ser maior ou igual a 0 e menor ou igual a %d\n", MEM_SIZE);
    return 0;
  }

  uint8_t byteIndexInInt = finalAddress % ADDRESS_STEP;
  int32_t mask = computeByteInIntExtractionMask(byteIndexInInt);

  return extractByteFromInt(mem[finalAddress], mask);
}

int32_t lbu(uint32_t address, int32_t kte) {
  return 0;
}

void sw(uint32_t address, int32_t kte, int32_t dado) {
  int32_t tempAddress = address + kte;

  if(!validateWordAddress(tempAddress)) {
    printf("O endereço %d fornecido é inválido! ", tempAddress);
    printf("O endereço deve ser divisível por %d e menor ou igual a %d.\n", ADDRESS_STEP, MEM_SIZE);
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
    printf("O endereço deve ser maior ou igual a 0 e menor ou igual a %d\n", MEM_SIZE);
    return;
  }

  uint8_t byteIndexInInt = tempAddress % ADDRESS_STEP;
  int32_t finalAddress = tempAddress - byteIndexInInt;
  int32_t expandedData = (dado << (byteIndexInInt * 8) & computeByteInIntExtractionMask(byteIndexInInt));
  uint32_t clearByteInPositionMask = ~computeByteInIntExtractionMask(byteIndexInInt);
  int32_t currentlyStoredWord = lw(finalAddress, 0);
  int32_t dataToBeStored = (currentlyStoredWord & clearByteInPositionMask) | expandedData;
  sw(finalAddress, 0, dataToBeStored);
}

int32_t* getMem() {
  return mem;
}

void resetMem() {
  int i = 0;
  for(i = 0; i < MEM_SIZE; i++) {
    mem[i] = 0;
  }
}

