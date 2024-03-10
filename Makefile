all: main

main: src/main.c src/cpu.c
	@gcc src/main.c src/cpu.c -o main.out -Wall

run: all
	@./main.out

clean:
	@rm -f main.out