#include "cpu.h"
#include "isa.h"



void CpuSetup(CPU* cpu){
    for(int i = 0; i < REG_AMOUNT; i++){
        cpu->reg[i] = 0;
    }
}

void CpuExecuteInstruction(CPU* cpu, uint32_t instr){
    DecodedInstruction dIns = {0};
    IsaDecodeInstruction(&dIns, instr);
    switch(dIns.op){
        case OP_MOVI:{
            RegImmeInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg] = instr.immediate; 
            break;
        }  
        case OP_MOV:{
            TwoRegInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg2] = cpu->reg[instr.reg1];
            break;
        }   
        case OP_ADD:{
            ThreeRegInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg1] = cpu->reg[instr.reg2] + cpu->reg[instr.reg3]; 
            break;
        }
        case OP_SUB:{
            ThreeRegInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg1] = cpu->reg[instr.reg2] - cpu->reg[instr.reg3]; 
            break;
        }
        case OP_MUL:{
            ThreeRegInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg1] = cpu->reg[instr.reg2] * cpu->reg[instr.reg3]; 
            break;
        }
        case OP_DIV:{
            ThreeRegInstruction instr = {0};
            IsaDecodeArgument((void*)&instr, &dIns);
            cpu->reg[instr.reg1] = cpu->reg[instr.reg2] / cpu->reg[instr.reg3]; 
            break;
        }
        default:
            NFAIL("Invalid op %d\n", dIns.op);
            break;
    }
    cpu->reg[PC]++;
}