/*
 * Trabalho 1 de OAC
 * Nome: Estevan Alexander de Paula
 * Matrícula: 17/0009611
 * Disciplina: Organização e Arqutetura de Computadores - Turma C
 * Compilador: gcc 11.1.0
 * SO: Linux
 * IDE: Vim
 * Resumo: o trabalho consiste em escrever, em C, funções que simulam
 *         instruções de manipulação e acesso à memória do conjunto
 *         de instruções RISC-V.
*/

#include <stdio.h>
#include "../src/riscv_memory.h"
#include "test.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* int32_t lbu(uint32_t address, int32_t kte); */

int main() {
  int totalTests = 0;
  int failedTests = 0;

  resetMem();

  printf("Testing sw\n");
  testSw(0, 0, 255, &totalTests, &failedTests);
  testSw(0, 4, 255, &totalTests, &failedTests);
  testSw(4, 8, 1024, &totalTests, &failedTests);
  testSw(2096, 1024, 0xFFFFFF, &totalTests, &failedTests);
  testSw(4096, 4, 0xABCDEF10, &totalTests, &failedTests);
  testSw(MEM_SIZE_IN_BYTES - 4, 0, 0xABCDEF10, &totalTests, &failedTests);
  printf("\n\n");

  printf("Testing sb\n");
  testSb(0, 1, 0xDA, 0xDA00, &totalTests, &failedTests);
  testSb(0, 3, 0xAB, 0xAB000000, &totalTests, &failedTests);
  testSb(4096, 2, 0xDB, 0x00DB0000, &totalTests, &failedTests);
  testSb(MEM_SIZE_IN_BYTES, -4, 0xA1, 0x000000A1, &totalTests, &failedTests);
  testSb(MEM_SIZE_IN_BYTES, -3, 0xB2, 0x0000B200, &totalTests, &failedTests);
  testSb(MEM_SIZE_IN_BYTES, -2, 0xC3, 0x00C30000, &totalTests, &failedTests);
  testSb(MEM_SIZE_IN_BYTES, -1, 0xD4, 0xD4000000, &totalTests, &failedTests);
  testSb(4, 8, 0xFF, 0xFF, &totalTests, &failedTests);
  sb(3, -3, 0xFF);sb(0, 1, 0xFF);sb(2, 0, 0xFF);sb(0, 3, 0xFF);testLw(0, 0, 0xFFFFFFFF, &totalTests, &failedTests);resetMem();
  sb(0, 0, 0x04);sb(0, 1, 0x03);sb(2, 0, 0x02);sb(0, 3, 0x01);testLw(0, 0, 0x01020304, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0xFF);sb(4, 1, 0xFE);sb(4, 2, 0xFD);sb(4, 3, 0xFC);testLw(4, 0, 0xFCFDFEFF, &totalTests, &failedTests);resetMem();
  printf("\n\n");

  printf("Testing lw\n");
  sw(0, 0, 255); testLw(0, 0, 255, &totalTests, &failedTests);
  sw(4, 56, 0x010203); testLw(4, 56, 0x010203, &totalTests, &failedTests);
  sw(13, 27, -23945); testLw(13, 27, -23945, &totalTests, &failedTests);
  sw(4095, 1, 42); testLw(4095, 1, 42, &totalTests, &failedTests);
  sw(MEM_SIZE_IN_BYTES, -4, 0x98765432); testLw(MEM_SIZE_IN_BYTES, -4, 0x98765432, &totalTests, &failedTests);
  printf("\n\n");

  printf("Testing lb\n");
  sb(0, 0, 0xAB); testLb(0, 0, 0xAB, &totalTests, &failedTests);resetMem();
  sb(0, 0, 0xBC); testLb(0, 0, 0xBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0x35); testLb(4, 0, 0x35, &totalTests, &failedTests);resetMem();
  sb(4, 3, 0xBC); testLb(4, 3, 0xBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0xAB); sb(4, 1, 0xCD); sb(4, 2, 0xEF); sb(4, 3, 0x01);
    testLb(4, 0, 0xAB, &totalTests, &failedTests);testLb(4, 1, 0xCD, &totalTests, &failedTests);
    testLb(4, 2, 0xEF, &totalTests, &failedTests);testLb(4, 3, 0x01, &totalTests, &failedTests);
    resetMem();
  sw(MEM_SIZE_IN_BYTES, -4, 0x98765432);
    testLb(MEM_SIZE_IN_BYTES, -4, 0x32, &totalTests, &failedTests);testLb(MEM_SIZE_IN_BYTES, -3, 0x54, &totalTests, &failedTests);
    testLb(MEM_SIZE_IN_BYTES, -2, 0x76, &totalTests, &failedTests);testLb(MEM_SIZE_IN_BYTES, -1, 0x98, &totalTests, &failedTests);
    resetMem();
  printf("\n\n");

  printf("Ran " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET
      " tests in total, of which "
      ANSI_COLOR_RED "%d" ANSI_COLOR_RESET
      " failed.\n", totalTests, failedTests);

  return 0;
}

void testSuccess(int *totalTests, int *failedTests) {
  printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
  *totalTests += 1;
}

void testFail(int *totalTests, int *failedTests) {
  printf(ANSI_COLOR_RED "x" ANSI_COLOR_RESET);
  *totalTests += 1;
  *failedTests += 1;
}

void testSw(uint32_t address, int32_t kte, int32_t dado, int *totalTests, int *failedTests) {
  sw(address, kte, dado);

  if(getMem()[(address + kte) / 4] == dado) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
  }

  resetMem();
}

void testSb(uint32_t address, int32_t kte, int8_t dado, int32_t expectedValue, int *totalTests, int *failedTests) {
  sb(address, kte, dado);
  uint8_t byteOffset = (address + kte) % 4;
  uint32_t baseAddress = (address + kte - byteOffset) / 4;

  if(getMem()[baseAddress] == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
  }

  resetMem();
}

void testLw(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests) {
  if(lw(address, kte) == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
    /* printf("\nExpected: %X\tGot: %X\n", expectedValue, lw(address, kte)); */
  }
}

void testLb(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests) {
  if(lb(address, kte) == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
    /* printf("\nExpected: %X\tGot: %X\n", expectedValue, lb(address, kte)); */
  }
}
