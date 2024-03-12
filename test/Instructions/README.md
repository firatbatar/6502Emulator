# Unit Tests for Instructions

This directory contains unit tests for the instructions.

## Folder Structure

Instructions are grouped as they are in the source code. Each group of instructions has its own directory. Each instruction has its own test file.  
The instructions that have tests are marked with :white_check_mark:.

_Note that the list only includes currently implemented instructions._
1. **`groupOne`** includes:
    - :white_check_mark: ORA
    - AND
    - EOR
    - ADC
    - STA
    - LDA
    - CMP
    - SBC
2. **`groupTwo`** includes:
    - ASL
    - ROL
    - LSR
    - ROR
    - STX
    - LDX
    - DEC
    - INC
3. **`groupThree`** includes:
    - BIT
    - JMP
    - JMP(abs)
    - STY
    - LDY
    - CPY
    - CPX


## Tests

Tests uses the [`Unity`](https://github.com/ThrowTheSwitch/Unity) framework.  
What tests are doing is to test each instruction with different addressing modes and see if the results on the internal registers and the memory are as expected.

## Running The tests

Each folder has its own `Makefile` to run the tests. To run the tests, navigate to the folder and run

```
$ make
```

or for separete build of each test file, run

```
$ make [instructionName]
```

This will compile the tests into separate executables, but it will not run them.

To run the tests, run

```
$ make run
```

Also note that, to clean the build files, run

```
$ make clean
```
