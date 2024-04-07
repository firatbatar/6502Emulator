unity := ../../src/unity.c ../../../src/cpu.c

all: BIT JMP STY LDY
	@echo "All group one tests compiled!"

BIT: $(unity) bit.c
	@gcc $(unity) bit.c -o bit.out -Wall

JMP: $(unity) jmp.c
	@gcc $(unity) jmp.c -o jmp.out -Wall

STY: $(unity) sty.c
	@gcc $(unity) sty.c -o sty.out -Wall

LDY: $(unity) ldy.c
	@gcc $(unity) ldy.c -o ldy.out -Wall

run: clean all
	@echo "\nRunning BIT tests..."
	@./bit.out
	@echo "\nRunning JMP tests..."
	@./jmp.out
	@echo "\nRunning STY tests..."
	@./sty.out
	@echo "\nRunning LDY tests..."
	@./ldy.out

clean:
	@find . -name "*.out" -type f -delete