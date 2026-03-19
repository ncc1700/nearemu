#include "isa.h"
#include "nearemu.h"
#include <stdint.h>




void IsaDecodeInstruction(DecodedInstruction* dIns, uint32_t eIns){
    dIns->op = eIns >> 24;
    dIns->arg = eIns & ((1 << 24) - 1);
    NINFO("OP: %d, ARG: %d\n", dIns->op, dIns->arg);
}

// UNSAFE, make SURE you are putting the correct type in the data argument
void IsaDecodeArgument(void* data, DecodedInstruction* dIns){
    switch(dIns->op){
        case OP_MOVI:{
            RegImmeInstruction* instr = (RegImmeInstruction*)data;
            instr->reg = dIns->arg >> 19;
            instr->immediate = dIns->arg & ((1 << 19) - 1);
            NINFO("OP: %d, REG: %d, IMME: %d\n", dIns->op, instr->reg, instr->immediate);
            break;
        }  
        
        case OP_MOV:{
            TwoRegInstruction* instr = (TwoRegInstruction*)data;
            instr->reg1 = dIns->arg >> 19;
            instr->reg2 = (dIns->arg >> 14) & ((1 << 5) - 1);
            NINFO("OP: %d, REG1: %d, REG2: %d\n", dIns->op, instr->reg1, instr->reg2);
            break;
        }   
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:{
            ThreeRegInstruction* instr = (ThreeRegInstruction*)data;
            instr->reg1 = dIns->arg >> 19;
            instr->reg2 = (dIns->arg >> 14) & ((1 << 5) - 1);
            instr->reg3 = (dIns->arg >> 9) & ((1 << 5) - 1);
            NINFO("OP: %d, REG1: %d, REG2: %d, REG3: %d\n", dIns->op, 
                                instr->reg1, instr->reg2, instr->reg3);
            break;
        }
        default:
            NFAIL("Invalid operand %d\n", dIns->op);
            break;
    }
}


void IsaEncodeInstruction(uint32_t* eIns, DecodedInstruction* dIns){
    *eIns = (dIns->op << 24) | (dIns->arg & ((1 << 24) - 1));
}

// UNSAFE, make SURE you are putting the correct type in the data argument
void IsaEncodeArgument(DecodedInstruction* dIns, Op op, void* data){
    dIns->op = op;
    switch(op){
        case OP_MOVI:{
            RegImmeInstruction* instr = (RegImmeInstruction*)data;
            dIns->arg = ((instr->reg & ((1 << 5) - 1)) << 19) | 
                        (instr->immediate & ((1 << 19) - 1));
            break;
        }  
        
        case OP_MOV:{
            TwoRegInstruction* instr = (TwoRegInstruction*)data;
            dIns->arg = ((instr->reg1 & ((1 << 5) - 1)) << 19) | 
                        ((instr->reg2 & ((1 << 5) - 1)) << 14);
            break;
        }   
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:{
            ThreeRegInstruction* instr = (ThreeRegInstruction*)data;
            dIns->arg = ((instr->reg1 & ((1 << 5) - 1)) << 19) | 
                        ((instr->reg2 & ((1 << 5) - 1)) << 14) |
                        ((instr->reg3 & ((1 << 5) - 1)) << 9);
            break;
        }
        default:
            NFAIL("Invalid op %d\n", op);
            break;
    }
}
