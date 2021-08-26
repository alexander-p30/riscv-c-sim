/*
 * Trabalho 1 de OAC
 * Nome: Estevan Alexander de Paula
 * Matrícula: 17/0009611
 * Disciplina: Organização e Arqutetura de Computadores - Turma C
 * Compilador: gcc 11.1.0
 * SO: Linux
 * IDE: Vim
 *
 * Uma forma rápida de testar o trabalho, rodando o programa na
 * pasta raíz, é rodar os seguintes comandos:
 *  - make compile
 *      Compila o projeto, incluindo o teste, e gera um binário
 *      riscv_sim
 *
 *  - make simulate
 *      Roda o binário riscv_sim, que carrega o programa da pasta raíz
 *      do projeto (a pasta anterior a esta)
 */

#include <stdio.h>
#include "../src/riscv_memory.h"
#include "../src/riscv_instructions.h"
#include "test.h"

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
  load_mem("text.bin", 0);
  load_mem("data.bin", 0x2000);
  run();

  return 0;
}

