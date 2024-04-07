unity := ../../src/unity.c ../../../src/cpu.c

all: BIT JMP STY LDY CPY CPX
	@echo "All group one tests compiled!"

BIT: $(unity) bit.c
	@gcc $(unity) bit.c -o bit.out -Wall

JMP: $(unity) jmp.c
	@gcc $(unity) jmp.c -o jmp.out -Wall

STY: $(unity) sty.c
	@gcc $(unity) sty.c -o sty.out -Wall

LDY: $(unity) ldy.c
	@gcc $(unity) ldy.c -o ldy.out -Wall

CPY: $(unity) cpy.c
	@gcc $(unity) cpy.c -o cpy.out -Wall

CPX: $(unity) cpx.c
	@gcc $(unity) cpx.c -o cpx.out -Wall

run: clean all
	@echo "\nRunning BIT tests..."
	@./bit.out
	@echo "\nRunning JMP tests..."
	@./jmp.out
	@echo "\nRunning STY tests..."
	@./sty.out
	@echo "\nRunning LDY tests..."
	@./ldy.out
	@echo "\nRunning CPY tests..."
	@./cpy.out
	@echo "\nRunning CPX tests..."
	@./cpx.out

clean:
	@find . -name "*.out" -type f -delete