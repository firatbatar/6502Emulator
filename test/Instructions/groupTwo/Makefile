unity := ../../src/unity.c ../../../src/cpu.c

all: ASL ROL LSR ROR STX LDX
	@echo "All group one tests compiled!"

ASL: $(unity) asl.c
	@gcc $(unity) asl.c -o asl.out -Wall

ROL: $(unity) rol.c
	@gcc $(unity) rol.c -o rol.out -Wall

LSR: $(unity) lsr.c
	@gcc $(unity) lsr.c -o lsr.out -Wall

ROR: $(unity) ror.c
	@gcc $(unity) ror.c -o ror.out -Wall

STX: $(unity) stx.c
	@gcc $(unity) stx.c -o stx.out -Wall

LDX: $(unity) ldx.c
	@gcc $(unity) ldx.c -o ldx.out -Wall

run: clean all
	@echo "\nRunning ASL tests..."
	@./asl.out
	@echo "\nRunning ROL tests..."
	@./rol.out
	@echo "\nRunning LSR tests..."
	@./lsr.out
	@echo "\nRunning ROR tests..."
	@./ror.out
	@echo "\nRunning STX tests..."
	@./stx.out
	@echo "\nRunning LDX tests..."
	@./ldx.out

clean:
	@find . -name "*.out" -type f -delete