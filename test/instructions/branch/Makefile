CC := gcc
CFLAGS := -Wall -I../../../include -I../../src -I../templates
SRC := ../../../src/cpu.c ../../../src/instructions.c
unity := ../../src/unity.c

all: bpl# bmi bvc bvs bcc bcs bne beq
	@echo "All branching tests compiled!"

%: %.c $(unity) $(SRC)
	@$(CC) -o $@.out $^ $(CFLAGS)

run: clean all
	@echo "\nRunning BPL tests..."
	@./bpl.out
#	@echo "\nRunning BMI tests..."
#	@./bmi.out
#	@echo "\nRunning BVC tests..."
#	@./bvc.out
#	@echo "\nRunning BVS tests..."
#	@./bvs.out
#	@echo "\nRunning BCC tests..."
#	@./bcc.out
#	@echo "\nRunning BCS tests..."
#	@./bcs.out
#	@echo "\nRunning BNE tests..."
#	@./bne.out
#	@echo "\nRunning BEQ tests..."
#	@./beq.out

clean:
	@rm -f *.out all