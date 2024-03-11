#include "../include/main.h"

void loadMemory(byte mem[], char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        exit(1);
    }

    char m;
    word idx = 0;
    while (!feof(file) && idx <= 0xFFFF) {
        m = fgetc(file);
        mem[idx] = (int8_t)m;
        idx++;
    }

    printf("Loaded memory from file \"%s\"\n", fileName);

    fclose(file);
}


int main(int argc, char *argv[]) {
    byte newMem[0x10000];

    switch (argc) {
    case 1:
        for (int i = 0; i <= 0xFFFF; i++) newMem[i] = 0xFF;
        break;
    case 2:
        loadMemory(newMem, argv[1]);
        break;
    default:
        fprintf(stderr, "Too many arguments!");
        exit(1);
        break;
    }

    initlizeCPU(newMem);


    int numOfInstructions = 2;

    for (int i = 0; i < numOfInstructions; i++) {
        execute();
    }

    printf("X: 0x%02X\n", X);
    printf("mem: 0x%02X\n", memory[0x0012]);

    return 0;
}