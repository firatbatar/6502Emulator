all: main

main: src/main.c src/cpu.c
	@gcc src/main.c src/cpu.c -o main.out -Wall

clean:
	@rm -f main.out