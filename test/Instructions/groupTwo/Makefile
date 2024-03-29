unity := ../../src/unity.c ../../../src/cpu.c

all: ASL
	@echo "All group one tests compiled!"

ASL: $(unity) asl.c
	@gcc $(unity) asl.c -o asl.out -Wall

run: clean all
	@echo "\nRunning ASL tests..."
	@./asl.out

clean:
	@find . -name "*.out" -type f -delete