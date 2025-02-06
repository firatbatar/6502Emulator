CC := gcc
CFLAGS := -Wall -I../../../include
SRC := ../../../src/cpu.c ../../../src/instructions.c
unity := ../../src/unity.c

all: asl rol lsr ror stx ldx dec inc
	@echo "All group one tests compiled!"

%: %.c $(unity) $(SRC)
	@$(CC) -o $@.out $^ $(CFLAGS)

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
	@echo "\nRunning DEC tests..."
	@./dec.out
	@echo "\nRunning INC tests..."
	@./inc.out

clean:
	@rm -f *.out all