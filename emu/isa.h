#ifndef ISA_H_INCLUDED
#define ISA_H_INCLUDED











#include "nearemu.h"
#include <stdint.h>

typedef enum _Op {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOV,
    OP_MOVI,
} Op;

typedef struct _DecodedInstruction {
    uint8_t op;
    uint32_t arg:24;
} DecodedInstruction;

// wish we had generics/templates in C =(

// register + register (for example mov)
typedef struct _TwoRegInstruction {
    uint16_t reg1:5;
    uint16_t reg2:5;
} TwoRegInstruction;

// register + register + register (for example add)
typedef struct _ThreeRegInstruction {
    uint16_t reg1:5;
    uint16_t reg2:5;
    uint16_t reg3:5;
} ThreeRegInstruction;

// register + immediate (for example movi)
typedef struct _RegImmeInstruction {
    uint32_t reg:5;
    uint32_t immediate:19;
} RegImmeInstruction;



void IsaDecodeInstruction(DecodedInstruction* dIns, uint32_t eIns);
void IsaDecodeArgument(void* data, DecodedInstruction* dIns);
void IsaEncodeInstruction(uint32_t* eIns, DecodedInstruction* dIns);
void IsaEncodeArgument(DecodedInstruction* dIns, Op op, void* data);



#endif