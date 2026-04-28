#ifndef ISA_H_INCLUDED
#define ISA_H_INCLUDED






#include <nearemu.h>

#define MAX_REG_AMOUNT 63
#define MAX_GENERAL_REG 30

typedef enum _Op {
    OP_ADD,
    OP_SUB,
    OP_MUL, 
    OP_DIV, 
    OP_MOV,
    OP_MOVI
} Op;

typedef enum _ArgType {
    ARG_TWO_IMME,
    ARG_TWO_REG, 
    ARG_THREE_REG
} ArgType;


typedef struct _DecodedInstruction {
    uint8_t op:8;
    uint32_t arg:24;
} DecodedInstruction;

typedef struct _DecodedArgImmeTwo {
    uint8_t reg:6;
    uint32_t imme:18;
} DecodedArgImmeTwo;

typedef struct _DecodedArgRegTwo {
    uint8_t reg1:6;
    uint8_t reg2:6;
} DecodedArgRegTwo;

typedef struct _DecodedArgRegThree {
    uint8_t reg1:6;
    uint8_t reg2:6;
    uint8_t reg3:6;
} DecodedArgRegThree;

uint32_t CpuEncodeInstruction(DecodedInstruction* decoded);
DecodedInstruction CpuDecodeInstruction(const uint32_t instruction);
uint32_t CpuEncodeArgImmeTwo(DecodedArgImmeTwo* decoded);
DecodedArgImmeTwo CpuDecodeArgImmeTwo(const uint32_t arg);
uint32_t CpuEncodeArgRegTwo(DecodedArgRegTwo* decoded);
DecodedArgRegTwo CpuDecodeArgRegTwo(const uint32_t arg);
uint32_t CpuEncodeArgRegThree(DecodedArgRegThree* decoded);
DecodedArgRegThree CpuDecodeArgRegThree(const uint32_t arg);
ArgType CpuGetArgTypeOfOp(const Op op);



#endif