#include <cpu/isa.h>



uint32_t CpuEncodeInstruction(DecodedInstruction* dInstr){
    uint32_t result = 0;
    result = dInstr->arg;
    result = (result << 8);
    result += dInstr->op;
    return result;
}

DecodedInstruction CpuDecodeInstruction(const uint32_t instruction){
    DecodedInstruction dInstr = {0};

    dInstr.op = (instruction & ~(1 << 9));
    dInstr.arg = (instruction >> 8);

    return dInstr;
}
