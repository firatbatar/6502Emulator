CC := gcc
CLFAGS := -g -Wall
source := ../../src/cpu.c ../../instructions.c
unity := ../src/unity.c

all: .groupOne .groupTwo .groupThree

.groupOne:
	@echo "\nRunning Group One tests..."
	cd ./groupOne && $(MAKE) run && $(MAKE) clean

.groupTwo:
	@echo "\nRunning Group Two tests..."
	cd ./groupTwo && $(MAKE) run && $(MAKE) clean

.groupThree:
	@echo "\nRunning Group Three tests..."
	cd ./groupThree && $(MAKE) run && $(MAKE) clean

clean:
	@cd ./groupOne && $(MAKE) clean
	@cd ./groupTwo && $(MAKE) clean
	@cd ./groupThree && $(MAKE) clean