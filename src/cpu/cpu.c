#include <cpu/cpu.h>
#include <cpu/isa.h>
#include <machine.h>














bool CpuSingleStep(NearMachine* mach){
    if(mach->cpu.reg[SREG_PC] >= (AMOUNT_OF_MEM - 3)){
        DEBUG_FAIL("Memory overflow on 0x%lx\n", mach->cpu.reg[SREG_PC]);
        return false;
    }
    uint32_t currentInstruction = ((uint32_t)mach->memory[mach->cpu.reg[SREG_PC]]) |
                                    ((uint32_t)mach->memory[mach->cpu.reg[SREG_PC] + 1] << 8) |
                                    ((uint32_t)mach->memory[mach->cpu.reg[SREG_PC] + 2] << 16) |
                                    ((uint32_t)mach->memory[mach->cpu.reg[SREG_PC] + 3] << 24);
    DecodedInstruction dInstr = CpuDecodeInstruction(currentInstruction);
    switch(dInstr.op){
        case OP_ADD:{
            DecodedArgRegThree dArg = CpuDecodeArgRegThree(dInstr.arg);
            if(dArg.reg1 > MAX_GENERAL_REG || dArg.reg2 > MAX_GENERAL_REG || dArg.reg3 > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on ADD (a1: %d, a2: %d, a3: %d)\n",
                            dArg.reg1, dArg.reg2, dArg.reg3);
                return false;
            }
            mach->cpu.reg[dArg.reg1] = mach->cpu.reg[dArg.reg2] + mach->cpu.reg[dArg.reg3];
            break;
        }
        case OP_SUB:{
            DecodedArgRegThree dArg = CpuDecodeArgRegThree(dInstr.arg);
            if(dArg.reg1 > MAX_GENERAL_REG || dArg.reg2 > MAX_GENERAL_REG || dArg.reg3 > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on SUB (a1: %d, a2: %d, a3: %d)\n",
                            dArg.reg1, dArg.reg2, dArg.reg3);
                return false;
            }
            mach->cpu.reg[dArg.reg1] = mach->cpu.reg[dArg.reg2] - mach->cpu.reg[dArg.reg3];
            break;
        }
        case OP_MUL:{
            DecodedArgRegThree dArg = CpuDecodeArgRegThree(dInstr.arg);
            if(dArg.reg1 > MAX_GENERAL_REG || dArg.reg2 > MAX_GENERAL_REG || dArg.reg3 > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on MUL (a1: %d, a2: %d, a3: %d)\n",
                            dArg.reg1, dArg.reg2, dArg.reg3);
                return false;
            }
            mach->cpu.reg[dArg.reg1] = mach->cpu.reg[dArg.reg2] * mach->cpu.reg[dArg.reg3];
            break;
        }
        case OP_DIV:{
            DecodedArgRegThree dArg = CpuDecodeArgRegThree(dInstr.arg);
            if(dArg.reg1 > MAX_GENERAL_REG || dArg.reg2 > MAX_GENERAL_REG || dArg.reg3 > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on DIV (a1: %d, a2: %d, a3: %d)\n",
                            dArg.reg1, dArg.reg2, dArg.reg3);
                return false;
            }
            if(mach->cpu.reg[dArg.reg3] == 0){
                DEBUG_FAIL("denominator is 0, division by 0 is undefined\n");
                return false;
            }
            mach->cpu.reg[dArg.reg1] = mach->cpu.reg[dArg.reg2] / mach->cpu.reg[dArg.reg3];
            break;
        }
        case OP_MOV:{
            DecodedArgRegTwo dArg = CpuDecodeArgRegTwo(dInstr.arg);
            if(dArg.reg1 > MAX_GENERAL_REG || dArg.reg2 > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on MOV (a1: %d, a2: %d)\n",
                            dArg.reg1, dArg.reg2);
                return false;
            }
            mach->cpu.reg[dArg.reg1] = mach->cpu.reg[dArg.reg2];
            break;
        }
        case OP_MOVI:{
            DecodedArgImmeTwo dArg = CpuDecodeArgImmeTwo(dInstr.arg);
            if(dArg.reg > MAX_GENERAL_REG){
                DEBUG_FAIL("Invalid register size on MOVI (a1: %d)\n",
                            dArg.reg);
                return false;
            }
            mach->cpu.reg[dArg.reg] = dArg.imme;
            break;
        }
        // case OP_STORE:{
        //     DecodedArgImmeTwo dArg = CpuDecodeArgImmeTwo(dInstr.arg);
        //     if(dArg.reg > MAX_GENERAL_REG){
        //         DEBUG_FAIL("Invalid register size on STORE (a1: %d)\n",
        //                     dArg.reg);
        //         return false;
        //     }
        //     if()
        //     mach->me = dArg.imme;
        // }
        default:
            DEBUG_FAIL("Invalid opcode on 0x%lx (%d)\n", mach->cpu.reg[SREG_PC], dInstr.op);
            return false;
    }

    mach->cpu.reg[SREG_PC] += 4;
    return true;
}