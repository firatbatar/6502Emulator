unity := ../../src/unity.c ../../../src/cpu.c

all: ORA AND EOR ADC

ORA: $(unity) ora.c
	@gcc $(unity) ora.c -o ora.out -Wall

AND: $(unity) and.c
	@gcc $(unity) and.c -o and.out -Wall

EOR: $(unity) eor.c
	@gcc $(unity) eor.c -o eor.out -Wall

ADC: $(unity) adc.c
	@gcc $(unity) adc.c -o adc.out -Wall

run: 
	@./ora.out
	@./and.out
	@./eor.out
	@./adc.out

clean:
	@find . -name "*.out" -type f -delete