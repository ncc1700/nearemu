#include "cpu.h"
#include "isa.h"
#include <stdio.h>







int main(){
    CPU cpu = {0};
    CpuSetup(&cpu);
    uint32_t eIns = 0;
    DecodedInstruction ins = {0};

    RegImmeInstruction instr = {1, 7};
    IsaEncodeArgument(&ins, OP_MOVI, &instr);
    IsaEncodeInstruction(&eIns, &ins);
    CpuExecuteInstruction(&cpu, eIns);

    instr = (RegImmeInstruction){2, 7};
    IsaEncodeArgument(&ins, OP_MOVI, &instr);
    IsaEncodeInstruction(&eIns, &ins);
    CpuExecuteInstruction(&cpu, eIns);

    ThreeRegInstruction tInstr = {3, 1, 2};
    IsaEncodeArgument(&ins, OP_ADD, &tInstr);
    IsaEncodeInstruction(&eIns, &ins);
    CpuExecuteInstruction(&cpu, eIns);
    NINFO("r3 = %lu\n", cpu.reg[3]);
}