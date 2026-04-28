#include <nearemu.h>
#include <cpu/isa.h>





int main(){
    DecodedArgRegThree first = {(1 << 3) - 1, (1 << 5) - 1, (1 << 6) - 1};
    uint32_t encoded = CpuEncodeArgRegThree(&first);
    DecodedArgRegThree decoded = CpuDecodeArgRegThree(encoded);
    DEBUG_PASS("INITIAL:\nReg1: %d, Reg2: %d, Reg3: %d\n\n", first.reg1, first.reg2, first.reg3);
    DEBUG_PASS("DECODED:\nReg1: %d, Reg2: %d, Reg3: %d\n\n", decoded.reg1, decoded.reg2, decoded.reg3);
    DEBUG_PASS("ENCODED: %u\n", encoded);
}