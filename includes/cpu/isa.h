#ifndef ISA_H_INCLUDED
#define ISA_H_INCLUDED






#include <nearemu.h>



typedef struct _DecodedInstruction {
    uint8_t op;
    uint32_t arg:24;
} DecodedInstruction;


uint32_t CpuEncodeInstruction(DecodedInstruction* dInstr);
DecodedInstruction CpuDecodeInstruction(const uint32_t instruction);










#endif