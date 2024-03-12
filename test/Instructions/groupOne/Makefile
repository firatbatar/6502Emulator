unity := ../../src/unity.c ../../../src/cpu.c

all: ORA

ORA: $(unity) ora.c
	@gcc $(unity) ora.c -o ora.out -Wall

run: 
	@./ora.out

clean:
	@find . -name "*.out" -type f -delete