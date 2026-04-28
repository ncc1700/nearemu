#include <cpu/isa.h>



static const ArgType opArgType[] = {
    [OP_ADD] = ARG_REG_THREE, 
    [OP_SUB] = ARG_REG_THREE, 
    [OP_MUL] = ARG_REG_THREE, 
    [OP_DIV] = ARG_REG_THREE, 
    [OP_MOV] = ARG_REG_TWO, 
    [OP_MOVI] = ARG_IMME_TWO
};


uint32_t CpuEncodeInstruction(DecodedInstruction* decoded){
    uint32_t result = 0;
    result = decoded->arg;
    result = (result << 8);
    result += decoded->op;
    return result;
}

DecodedInstruction CpuDecodeInstruction(const uint32_t instruction){
    DecodedInstruction decoded = {0};

    decoded.op = (instruction & ~(1 << 9));
    decoded.arg = (instruction >> 8);

    return decoded;
}

uint32_t CpuEncodeArgImmeTwo(DecodedArgImmeTwo* decoded){
    uint32_t result = 0;
    result = decoded->imme;
    result = (result << 6);
    result += decoded->reg;
    return result;
}

DecodedArgImmeTwo CpuDecodeArgImmeTwo(const uint32_t arg){
    DecodedArgImmeTwo decoded = {0};
    if(arg > ((1 << 24) - 1)){
        // TODO (for me): panic and die here, theres an error
        DEBUG_FAIL("Argument is LARGER then the limit!\n");
        return decoded;
    }
    decoded.reg = (arg & ~(1 << 19));
    decoded.imme = (arg >> 6);
    return decoded;
}


uint32_t CpuEncodeArgRegTwo(DecodedArgRegTwo* decoded){
    uint32_t result = 0;
    result = decoded->reg2;
    result = (result << 6);
    result += decoded->reg1;
    return result;
}

DecodedArgRegTwo CpuDecodeArgRegTwo(const uint32_t arg){
    DecodedArgRegTwo decoded = {0};
    if(arg > ((1 << 24) - 1)){
        // panic and die here, theres an error
        DEBUG_FAIL("Argument is LARGER then the limit!\n");
        return decoded;
    }
    decoded.reg1 = (arg & ~(1 << 7));
    decoded.reg2 = (arg >> 6);
    return decoded;
}

uint32_t CpuEncodeArgRegThree(DecodedArgRegThree* decoded){
    uint32_t result = 0;
    result = decoded->reg3;
    result = (result << 6);
    result += decoded->reg2;
    result = (result << 6);
    result += decoded->reg1;
    return result;
}

DecodedArgRegThree CpuDecodeArgRegThree(const uint32_t arg){
    DecodedArgRegThree decoded = {0};
    if(arg > ((1 << 24) - 1)){
        // panic and die here, theres an error
        DEBUG_FAIL("Argument is LARGER then the limit!\n");
        return decoded;
    }
    decoded.reg1 = (arg & ~(1 << 13));
    uint32_t split = (arg >> 6);
    decoded.reg2 = (split & ~(1 << 7));
    decoded.reg3 = (split >> 6);
    return decoded;
}


ArgType CpuGetArgTypeOfOp(const Op op){
    uint32_t size = (sizeof(opArgType)) / sizeof((opArgType[0]));
    if(op >= size){
        DEBUG_FAIL("Op is not defined\n");
        return 0; // TODO (for me): panic and die here
    }
    return opArgType[op];
}