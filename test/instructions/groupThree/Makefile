CC := gcc
CFLAGS := -Wall -I../../../include -I../../src -I../templates
SRC := ../../../src/cpu.c ../../../src/instructions.c
unity := ../../src/unity.c

all: bit jmp sty ldy cpy cpx
	@echo "All group one tests compiled!"

%: %.c $(unity) $(SRC)
	@$(CC) -o $@.out $^ $(CFLAGS)

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
	@rm -f *.out all