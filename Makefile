CC := gcc
CFLAGS := -Wall -Iinclude
SRC := src/main.c src/cpu.c
TARGET := main.out

main: $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	@rm -f $(TARGET)