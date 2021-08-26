compile:
	ls **/*.c | xargs gcc -o riscv_sim -g

simulate:
	./riscv_sim

