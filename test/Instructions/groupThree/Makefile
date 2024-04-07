unity := ../../src/unity.c ../../../src/cpu.c

all: BIT JMP
	@echo "All group one tests compiled!"

BIT: $(unity) bit.c
	@gcc $(unity) bit.c -o bit.out -Wall

JMP: $(unity) jmp.c
	@gcc $(unity) jmp.c -o jmp.out -Wall

run: clean all
	@echo "\nRunning BIT tests..."
	@./bit.out
	@echo "\nRunning JMP tests..."
	@./jmp.out

clean:
	@find . -name "*.out" -type f -delete