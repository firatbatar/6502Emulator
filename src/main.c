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

    newMem[0xFFFC] = 0x42;
    newMem[0xFFFD] = 0x42;
    newMem[0x4242] = INS_LDA_IM;
    newMem[0x4243] = 0x01;
    newMem[0x4244] = INS_ADC_IM;
    newMem[0x4245] = 0x10;
    newMem[0x4246] = INS_STA_ZP;
    newMem[0x4247] = 0x40;

    initlizeCPU(newMem);

    int numOfInstructions = 3;

    for (int i = 0; i < numOfInstructions; i++) {
        execute();
    }

    printf("A: 0x%02X\n", A);
    printf("mem: 0x%02X\n", memory[0x0040]);

    return 0;
}