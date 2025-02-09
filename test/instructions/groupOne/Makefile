CC := gcc
CFLAGS := -Wall -I../../../include -I../../src -I../templates
SRC := ../../../src/cpu.c ../../../src/instructions.c
unity := ../../src/unity.c

all: ora and eor adc sta lda sbc cmp
	@echo "All group one tests compiled!"

%: %.c $(unity) $(SRC)
	@$(CC) -o $@.out $^ $(CFLAGS)

run: clean all
	@echo "\nRunning ORA tests..."
	@./ora.out
	@echo "\nRunning AND tests..."
	@./and.out
	@echo "\nRunning EOR tests..."
	@./eor.out
	@echo "\nRunning ADC tests..."
	@./adc.out
	@echo "\nRunning STA tests..."
	@./sta.out
	@echo "\nRunning LDA tests..."
	@./lda.out
	@echo "\nRunning CMP tests..."
	@./cmp.out
	@echo "\nRunning SBC tests..."
	@./sbc.out

clean:
	@rm -f *.out all