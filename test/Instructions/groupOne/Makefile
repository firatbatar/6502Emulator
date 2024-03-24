unity := ../../src/unity.c ../../../src/cpu.c

all: ORA AND EOR ADC SBC CMP
	@echo "All group one tests compiled!"

ORA: $(unity) ora.c
	@gcc $(unity) ora.c -o ora.out -Wall

AND: $(unity) and.c
	@gcc $(unity) and.c -o and.out -Wall

EOR: $(unity) eor.c
	@gcc $(unity) eor.c -o eor.out -Wall

ADC: $(unity) adc.c
	@gcc $(unity) adc.c -o adc.out -Wall

CMP: $(unity) cmp.c
	@gcc $(unity) cmp.c -o cmp.out -Wall

SBC: $(unity) sbc.c
	@gcc $(unity) sbc.c -o sbc.out -Wall

run: clean all
	@echo "\nRunning ORA tests..."
	@./ora.out
	@echo "\nRunning AND tests..."
	@./and.out
	@echo "\nRunning EOR tests..."
	@./eor.out
	@echo "\nRunning ADC tests..."
	@./adc.out
	@echo "\nRunning CMP tests..."
	@./cmp.out
	@echo "\nRunning SBC tests..."
	@./sbc.out

clean:
	@find . -name "*.out" -type f -delete