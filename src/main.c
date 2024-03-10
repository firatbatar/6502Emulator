#include "../include/main.h"

int main(int argc, char *argv[]) {
    // byte newMem[0x10000];
    
    // resetMemory();
    // setMemory(newMem);
    resetCPU();

    int numOfInstructions = 3;

    for (int i = 0; i < numOfInstructions; i++) {
        execute();
    }

    printf("A: 0x%02X\n", A);

    return 0;
}