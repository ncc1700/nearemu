#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED


#include <nearemu.h>
#include <cpu/isa.h>

#define AMOUNT_OF_MEM (96 * 1024) // 96KB

typedef struct _CPU {
    uint64_t reg[MAX_REG_AMOUNT];
} CPU;

typedef struct _NearMachine {
    CPU cpu;
    uint8_t memory[AMOUNT_OF_MEM];
} NearMachine;























#endif