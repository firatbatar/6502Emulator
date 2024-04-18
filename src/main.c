#include <stdio.h>
#include <stdlib.h>
#include "../include/cpu.h"
#include "../include/instructions.h"

int main(int argc, char *argv[]) {
    byte newMem[0x10000];
    char *fileName = NULL;

    switch (argc) {
    case 1:
        for (int i = 0; i <= 0xFFFF; i++) newMem[i] = 0xFF;
        break;
    case 2:
        fileName = argv[1];
        break;
    default:
        fprintf(stderr, "Too many arguments!");
        exit(1);
        break;
    }

    initlizeCPU(newMem, fileName);

    int numOfInstructions = 0;

    for (int i = 0; i < numOfInstructions; i++) {
        execute();
    }

    return 0;
}