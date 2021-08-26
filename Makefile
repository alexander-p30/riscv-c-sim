compile:
	@echo -e "\x1b[34m\n=> Compiling...\n\x1b[0m"
	ls **/*.c | xargs gcc -o riscv_sim -g

simulate:
	@echo -e "\x1b[34m\n=> Running simulation...\n\x1b[0m"
	./riscv_sim

test_testador: compile
	@echo -e "\x1b[34m\n=> Preparing test...\n\x1b[0m"
	cp bin/testador_data.bin data.bin
	cp bin/testador_text.bin text.bin
	@echo -e "\x1b[34m\n=> Running test...\n\x1b[0m"
	./riscv_sim

test_nop:
	@echo -e "\x1b[34m\n=> Preparing test...\n\x1b[0m"
	cp src/riscv_instructions.c src/riscv_instructions.bak
	cp src/riscv_instructions_for_nop_test src/riscv_instructions.c
	cp bin/nop_data.bin data.bin
	cp bin/nop_text.bin text.bin
	@echo -e "\x1b[34m\n=> Compiling with monkey patch...\n\x1b[0m"
	ls **/*.c | xargs gcc -o riscv_sim -g
	@echo -e "\x1b[34m\n=> Running test...\n\x1b[0m"
	./riscv_sim
	@echo -e "\x1b[34m\n=> Undoing monkey patch and recompiling...\n\x1b[0m"
	mv src/riscv_instructions.bak src/riscv_instructions.c
	ls **/*.c | xargs gcc -o riscv_sim -g

test_jalr: compile
	@echo -e "\x1b[34m\n=> Preparing test...\n\x1b[0m"
	cp bin/jalr_data.bin data.bin
	cp bin/jalr_text.bin text.bin
	@echo -e "\x1b[34m\n=> Running test...\n\x1b[0m"
	./riscv_sim

test_sltu: compile
	@echo -e "\x1b[34m\n=> Preparing test...\n\x1b[0m"
	cp bin/sltu_data.bin data.bin
	cp bin/sltu_text.bin text.bin
	@echo -e "\x1b[34m\n=> Running test...\n\x1b[0m"
	./riscv_sim

