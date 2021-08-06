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
 *
 * Uma forma rápida de testar o trabalho, executando a bateria de
 * testes abaixo, é rodar os seguintes comandos:
 *  - make compile
 *      Compila o projeto, incluindo o teste, e gera um binário
 *      test_sim
 *
 *  - make simulate
 *      Roda o binário test_sim, que roda os testes automatizados
 *      e printa o seu sucesso ou falha, e printa os testes
 *      verbosos, que deixam os valores explícitos
*/

#include <stdio.h>
#include "../src/riscv_memory.h"
#include "test.h"

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* int32_t lbu(uint32_t address, int32_t kte); */

int main() {
  int totalTests = 0;
  int failedTests = 0;

  resetMem();

  printf("-----Testes automatizados (utilizados durante o desenvolvimento)-----\n\n");

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
  sb(0, 0, 0xAB); testLb(0, 0, 0xFFFFFFAB, &totalTests, &failedTests);resetMem();
  sb(0, 0, 0xBC); testLb(0, 0, 0xFFFFFFBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0x35); testLb(4, 0, 0x35, &totalTests, &failedTests);resetMem();
  sb(4, 3, 0xBC); testLb(4, 3, 0xFFFFFFBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0xAB); sb(4, 1, 0xCD); sb(4, 2, 0xEF); sb(4, 3, 0x01);
    testLb(4, 0, 0xFFFFFFAB, &totalTests, &failedTests);testLb(4, 1, 0xFFFFFFCD, &totalTests, &failedTests);
    testLb(4, 2, 0xFFFFFFEF, &totalTests, &failedTests);testLb(4, 3, 0x01, &totalTests, &failedTests);
    resetMem();
  sw(MEM_SIZE_IN_BYTES, -4, 0x98765432);
    testLb(MEM_SIZE_IN_BYTES, -4, 0x32, &totalTests, &failedTests);testLb(MEM_SIZE_IN_BYTES, -3, 0x54, &totalTests, &failedTests);
    testLb(MEM_SIZE_IN_BYTES, -2, 0x76, &totalTests, &failedTests);testLb(MEM_SIZE_IN_BYTES, -1, 0xFFFFFF98, &totalTests, &failedTests);
    resetMem();
  printf("\n\n");

  printf("Testing lbu\n");
  sb(0, 0, 0xAB); testLbu(0, 0, 0xAB, &totalTests, &failedTests);resetMem();
  sb(0, 0, 0xBC); testLbu(0, 0, 0xBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0x35); testLbu(4, 0, 0x35, &totalTests, &failedTests);resetMem();
  sb(4, 3, 0xBC); testLbu(4, 3, 0xBC, &totalTests, &failedTests);resetMem();
  sb(4, 0, 0xAB); sb(4, 1, 0xCD); sb(4, 2, 0xEF); sb(4, 3, 0x01);
    testLbu(4, 0, 0xAB, &totalTests, &failedTests);testLbu(4, 1, 0xCD, &totalTests, &failedTests);
    testLbu(4, 2, 0xEF, &totalTests, &failedTests);testLbu(4, 3, 0x01, &totalTests, &failedTests);
    resetMem();
  sw(MEM_SIZE_IN_BYTES, -4, 0x98765432);
    testLbu(MEM_SIZE_IN_BYTES, -4, 0x32, &totalTests, &failedTests);testLbu(MEM_SIZE_IN_BYTES, -3, 0x54, &totalTests, &failedTests);
    testLbu(MEM_SIZE_IN_BYTES, -2, 0x76, &totalTests, &failedTests);testLbu(MEM_SIZE_IN_BYTES, -1, 0x98, &totalTests, &failedTests);
    resetMem();
  printf("\n\n");

  printf("Ran " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET
      " tests in total, of which "
      ANSI_COLOR_RED "%d" ANSI_COLOR_RESET
      " failed.\n", totalTests, failedTests);

  printf("\n-----Testes \"verbosos\"-----\n");

  printf("\nLegenda:");
  printf(ANSI_COLOR_BLUE "\n\t- Código rodado" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_MAGENTA "\n\t- Resultado" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_RED "\n\t- Mensagem de erro\n" ANSI_COLOR_RESET);

  printf(ANSI_COLOR_GREEN "\n======Primeiro cenário======\n" ANSI_COLOR_RESET);
  sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01);
  sb(4, 0, 0xAB); sb(4, 1, 0xCD); sb(4, 2, 0xEF); sb(4, 3, 0x11);
  sw(12, 0, 0xFF);
  sw(16, 0, 0xFFFF);
  sw(20, 0, 0xFFFFFFFF);
  sw(24, 0, 0x80000000);

  printf(ANSI_COLOR_BLUE);
  printf("sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01); \n");
  printf("sb(4, 0, 0xAB); sb(4, 1, 0xCD); sb(4, 2, 0xEF); sb(4, 3, 0x11);\n");
  printf("sw(12, 0, 0xFF);\n");
  printf("sw(16, 0, 0xFFFF);\n");
  printf("sw(20, 0, 0xFFFFFFFF);\n");
  printf("sw(24, 0, 0x80000000);\n");

  printf(ANSI_COLOR_RESET ANSI_COLOR_MAGENTA);
  printf("\nmem[0] = %X\n", getMem()[0]);
  printf("mem[1] = %X\n", getMem()[1]);
  printf("mem[2] = %X\n", getMem()[2]);
  printf("mem[3] = %X\n", getMem()[3]);
  printf("mem[4] = %X\n", getMem()[4]);
  printf("mem[5] = %X\n", getMem()[5]);
  printf("mem[6] = %X\n", getMem()[6]);

  printf("\nlb(4,0): %X\n", lb(4,0));
  printf("lb(4,1): %X\n", lb(4,1));
  printf("lb(4,2): %X\n", lb(4,2));
  printf("lb(4,3): %X\n", lb(4,3));
  printf("lbu(4,0): %X\n", lbu(4,0));
  printf("lbu(4,1): %X\n", lbu(4,1));
  printf("lbu(4,2): %X\n", lbu(4,2));
  printf("lbu(4,3): %X\n", lbu(4,3));
  printf("lw(12,0): %X\n", lw(12,0));
  printf("lw(16, 0): %X\n", lw(16, 0));
  printf("lw(20,0): %X\n", lw(20,0));
  printf(ANSI_COLOR_RESET);

  printf(ANSI_COLOR_GREEN "\n======Segundo cenário======\n" ANSI_COLOR_RESET);
  printf("Testando inserir palavras e bytes no limite da memória, ou seja, no endereço %d.\n", MEM_SIZE_IN_BYTES - 1);

  sw(MEM_SIZE_IN_BYTES, -4, 0x98765432);
  printf(ANSI_COLOR_BLUE "sw(%d, -4, 0x98765432);\n", MEM_SIZE_IN_BYTES);
  printf(ANSI_COLOR_MAGENTA "mem[%d] = %X\n\n" ANSI_COLOR_RESET, MEM_SIZE_IN_BYTES - 1, getMem()[(MEM_SIZE_IN_BYTES / 4) - 1]);

  sb(MEM_SIZE_IN_BYTES, -2, 0xAA);
  printf(ANSI_COLOR_BLUE "sb(MEM_SIZE_IN_BYTES, -2, 0xAA);\n", MEM_SIZE_IN_BYTES);
  printf(ANSI_COLOR_MAGENTA "mem[%d] = %X\n\n" ANSI_COLOR_RESET, MEM_SIZE_IN_BYTES - 1, getMem()[(MEM_SIZE_IN_BYTES / 4) - 1]);

  sb(MEM_SIZE_IN_BYTES, -4, 0xBB);
  printf(ANSI_COLOR_BLUE "sb(MEM_SIZE_IN_BYTES, -4, 0xBB);\n", MEM_SIZE_IN_BYTES);
  printf(ANSI_COLOR_MAGENTA "mem[%d] = %X\n\n" ANSI_COLOR_RESET, MEM_SIZE_IN_BYTES - 1, getMem()[(MEM_SIZE_IN_BYTES / 4) - 1]);

  sb(MEM_SIZE_IN_BYTES, -1, 0xCC);
  printf(ANSI_COLOR_BLUE "sb(MEM_SIZE_IN_BYTES, -1, 0xCC);\n", MEM_SIZE_IN_BYTES);
  printf(ANSI_COLOR_MAGENTA "mem[%d] = %X\n\n" ANSI_COLOR_RESET, MEM_SIZE_IN_BYTES - 1, getMem()[(MEM_SIZE_IN_BYTES / 4) - 1]);

  sb(MEM_SIZE_IN_BYTES, -4, 0xEA);sb(MEM_SIZE_IN_BYTES, -3, 0xEB);sb(MEM_SIZE_IN_BYTES, -2, 0xEC);sb(MEM_SIZE_IN_BYTES, -1, 0xED);
  printf(ANSI_COLOR_BLUE);
  printf("sb(%d, -4, 0xEA);", MEM_SIZE_IN_BYTES);
  printf("sb(%d, -3, 0xEB);", MEM_SIZE_IN_BYTES);
  printf("sb(%d, -2, 0xEC);", MEM_SIZE_IN_BYTES);
  printf("sb(%d, -1, 0xED);\n", MEM_SIZE_IN_BYTES);
  printf(ANSI_COLOR_MAGENTA "mem[%d] = %X\n" ANSI_COLOR_RESET, MEM_SIZE_IN_BYTES - 1, getMem()[(MEM_SIZE_IN_BYTES / 4) - 1]);
  printf(ANSI_COLOR_RESET);

  printf(ANSI_COLOR_GREEN "\n======Terceiro cenário======\n" ANSI_COLOR_RESET);
  printf("Testando que as validações são aplicadas e as mensagens de erro, exibidas.\n\n");

  printf(ANSI_COLOR_BLUE "sb(-1, 0, 0);\n");
  printf(ANSI_COLOR_RED);sb(-1, 0, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "sb(16384, 0, 0);\n");
  printf(ANSI_COLOR_RED);sb(16384, 0, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lb(-1, 0);\n");
  printf(ANSI_COLOR_RED);lb(-1, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lb(16384, 0);\n");
  printf(ANSI_COLOR_RED);lb(16384, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lbu(-1, 0);\n");
  printf(ANSI_COLOR_RED);lbu(-1, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lbu(16384, 0);\n");
  printf(ANSI_COLOR_RED);lbu(16384, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "sw(-1, 0, 0);\n");
  printf(ANSI_COLOR_RED);sw(-1, 0, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "sw(16384, 0, 0);\n");
  printf(ANSI_COLOR_RED);sw(16384, 0, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "sw(5, 0, 0);\n");
  printf(ANSI_COLOR_RED);sw(5, 0, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lw(-1, 0);\n");
  printf(ANSI_COLOR_RED);lw(-1, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lw(16384, 0);\n");
  printf(ANSI_COLOR_RED);lw(16384, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lw(16381, 0);\n");
  printf(ANSI_COLOR_RED);lw(16381, 0);printf(ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BLUE "lw(5, 0);\n");
  printf(ANSI_COLOR_RED);lw(5, 0);printf(ANSI_COLOR_RESET);

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
  }
}

void testLb(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests) {
  if(lb(address, kte) == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
  }
}

void testLbu(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests) {
  if(lbu(address, kte) == expectedValue) {
    testSuccess(totalTests, failedTests);
  } else {
    testFail(totalTests, failedTests);
  }
}
