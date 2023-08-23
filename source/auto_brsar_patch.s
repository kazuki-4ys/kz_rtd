#include <ppc-asm.h>

.global get_auto_brsar_patch_asm
.global get_auto_brsar_patch_asm_end

.macro defaultInstruction
    lwz r3, -0x6C40 (r13)
.endm

.macro pushStack
    stwu sp, -0x80 (sp)#124 + パディング
    mflr r0
    stw r0, 0x84 (sp)
    stmw r3, 8 (sp)
.endm

.macro popStack
    lmw r3, 8 (sp)
    lwz r0, 0x84 (sp)
    mtlr r0
    addi sp, sp, 0x80
.endm

get_auto_brsar_patch_asm_end:
    mflr r12
    b get_auto_brsar_patch_asm_end_b
get_auto_brsar_patch_asm:
    mflr r12
bl blTrickCommonEnd
auto_brsar_patch_asm:

#by Elias_
#https://www.youtube.com/watch?v=y2tOmsdoBjw
    lis r31, 0x7FFF
    ori r31, r31, 0xFFFF
    stw r31, 0x74(r29)
	.long 0
get_auto_brsar_patch_asm_end_b:
    bl blTrickCommonEnd