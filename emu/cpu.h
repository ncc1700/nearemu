#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED








#include "nearemu.h"

#define REG_AMOUNT 31

typedef enum _SpecialRegister {
    PC = 15,
    ADD = 16,
} SpecialRegister;


typedef struct _CPU {
    uint64_t reg[REG_AMOUNT];
} CPU;


void CpuSetup(CPU* cpu);
void CpuExecuteInstruction(CPU* cpu, uint32_t instr);








#endif