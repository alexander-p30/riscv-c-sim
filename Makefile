compile:
	ls **/*.c | xargs gcc -o test_sim -g

simulate:
	./test_sim

