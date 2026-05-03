#include <nearemu.h>
#include <cpu/isa.h>
#include <machine.h>
#include <cpu/cpu.h>
#include <string.h>



int main(){
    NearMachine machine = {0};
    uint32_t instruction[4] = {0};

    // movi r0, 10
    DecodedInstruction dInstr = {.op = OP_MOVI, .arg = 0};
    DecodedArgImmeTwo dArg1 = {.reg = 0, .imme = 10};
    dInstr.arg = CpuEncodeArgImmeTwo(&dArg1);
    instruction[0] = CpuEncodeInstruction(&dInstr);

    // movi r1, 10
    dInstr = (DecodedInstruction){.op = OP_MOVI, .arg = 0};
    DecodedArgImmeTwo dArg2 = {.reg = 1, .imme = 10};
    dInstr.arg = CpuEncodeArgImmeTwo(&dArg2);
    instruction[1] = CpuEncodeInstruction(&dInstr);

    // add r2, r0, r1
    dInstr = (DecodedInstruction){.op = OP_ADD, .arg = 0};
    DecodedArgRegThree dArg3 = {.reg1 = 2, .reg2 = 0, .reg3 = 1};
    dInstr.arg = CpuEncodeArgRegThree(&dArg3);
    instruction[2] = CpuEncodeInstruction(&dInstr);
    
    memcpy((uint8_t*)machine.memory, (uint8_t*)instruction, sizeof(instruction));

    machine.cpu.reg[SREG_PC] = 0x0;
    for(int i = 0; i < 3; i++){
        bool result = CpuSingleStep(&machine);
        if(result == false){
            DEBUG_FAIL("failed at %d\n", i);
            break;
        }
    }

    DEBUG_INFO("register 2 is %ld\n", machine.cpu.reg[2]);
}

