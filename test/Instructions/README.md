# Unit Tests for Instructions

This directory contains unit tests for the instructions.

## Test Templates

Since most of the instruction do similar actions as they are performing their instruction I will write some templates to re-use.  
**Disclaimer:** They are very messy at the moment since I am writing them as I, as I need. Probably I could have been much clever with them, perhaps I will return them later.  
Templates can be found in [`templates`](./templates/) folder.

## Folder Structure

Instructions are grouped as they are in the source code. Each group of instructions has its own directory. Each instruction has its own C file.  
The instructions that have tests are marked with :white_check_mark:.

_Note that the list only includes currently implemented instructions._
1. **`groupOne`** includes:
    - :white_check_mark: ORA
    - :white_check_mark: AND
    - :white_check_mark: EOR
    - :white_check_mark: ADC
    - :white_check_mark: STA
    - :white_check_mark: LDA
    - :white_check_mark: CMP
    - :white_check_mark: SBC
2. **`groupTwo`** includes:
    - :white_check_mark: ASL
    - :white_check_mark: ROL
    - :white_check_mark: LSR
    - :white_check_mark: ROR
    - :white_check_mark: STX
    - :white_check_mark: LDX
    - :white_check_mark: DEC
    - :white_check_mark: INC
3. **`groupThree`** includes:
    - :white_check_mark: BIT
    - :white_check_mark: JMP
    - :white_check_mark: JMP(abs)
    - :white_check_mark: STY
    - :white_check_mark: LDY
    - :white_check_mark: CPY
    - :white_check_mark: CPX


## Tests

Tests uses the [`Unity`](https://github.com/ThrowTheSwitch/Unity) framework.  
What tests are doing is to test each instruction with different addressing modes and see if the results on the internal registers and the memory are as expected.  

## Running The tests

Each folder has its own `Makefile` to build and run the tests. To build the tests, navigate to the folder and run

```
$ make
```

or for separete build of each test file, use

```
$ make [instructionName]
```

This will compile the tests into separate executables, but it will not run them.

To run the tests, use

```
$ make run
```
Note that `run` will automatically perform a `make all` command before hand.

To clean the build files, run

```
$ make clean
```
