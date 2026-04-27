#include <nearemu.h>
#include <cpu/isa.h>





int main(){
    DecodedInstruction first = {255, ((1 << 24) - 1)};
    uint32_t encoded = CpuEncodeInstruction(&first);
    DecodedInstruction decoded = CpuDecodeInstruction(encoded);
    DEBUG_PASS("INITIAL:\nOp: %d, Arg: %d\n\n", first.op, first.arg);
    DEBUG_PASS("DECODED:\nOp: %d, Arg: %d\n\n", decoded.op, decoded.arg);
    DEBUG_PASS("ENCODED: %u\n", encoded);
}