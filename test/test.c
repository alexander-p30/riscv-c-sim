#include <stdio.h>
#include "../src/riscv_memory.h"
#include "test.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* int32_t lb(uint32_t address, int32_t kte); */

/* int32_t lbu(uint32_t address, int32_t kte); */

/* void sw(uint32_t address, int32_t kte, int32_t dado); */

/* void sb(uint32_t address, int32_t kte, int8_t dado); */

int main() {
  int totalTests = 0;
  int failedTests = 0;

  resetMem();

  printf("Testing sw\n");
  testSw(0, 0, 255, &totalTests, &failedTests);
  testSw(0, 4, 255, &totalTests, &failedTests);
  testSw(4, 8, 1024, &totalTests, &failedTests);
  testSw(2096, 1024, 0xFFFFFF, &totalTests, &failedTests);
  printf("\n\n");

  printf("Testing sb\n");
  testSb(0, 1, 0xDA, 0xDA00, &totalTests, &failedTests);
  testSb(0, 3, 0xAB, 0xAB000000, &totalTests, &failedTests);
  testSb(4096, 2, 0xDB, 0xDB0000, &totalTests, &failedTests);
  testSb(4, 8, 0xFF, 0xFF, &totalTests, &failedTests);
  sb(3, -3, 0xFF);sb(0, 1, 0xFF);sb(2, 0, 0xFF);sb(0, 3, 0xFF);testLw(0, 0, 0xFFFFFFFF, &totalTests, &failedTests);resetMem();
  sb(0, 0, 0x04);sb(0, 1, 0x03);sb(2, 0, 0x02);sb(0, 3, 0x01);testLw(0, 0, 0x01020304, &totalTests, &failedTests);resetMem();
  printf("\n\n");

  printf("Testing lw\n");
  sw(0, 0, 255); testLw(0, 0, 255, &totalTests, &failedTests);
  sw(4, 56, 0x010203); testLw(4, 56, 0x010203, &totalTests, &failedTests);
  sw(13, 27, -23945); testLw(13, 27, -23945, &totalTests, &failedTests);
  sw(4095, 1, 42); testLw(4095, 1, 42, &totalTests, &failedTests);
  printf("\n\n");

  printf("\nRan " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET
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

void testLw(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests) {
  if(lw(address, kte) == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
  }
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
