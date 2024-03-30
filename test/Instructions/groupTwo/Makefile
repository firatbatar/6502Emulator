unity := ../../src/unity.c ../../../src/cpu.c

all: ASL ROL
	@echo "All group one tests compiled!"

ASL: $(unity) asl.c
	@gcc $(unity) asl.c -o asl.out -Wall

ROL: $(unity) rol.c
	@gcc $(unity) rol.c -o rol.out -Wall

run: clean all
	@echo "\nRunning ASL tests..."
	@./asl.out
	@echo "\nRunning ROL tests..."
	@./rol.out

clean:
	@find . -name "*.out" -type f -delete