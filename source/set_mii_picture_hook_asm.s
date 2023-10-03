#include <ppc-asm.h>

.global set_mii_picture_hook_asm
.global set_mii_picture_hook_asm_end

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

set_mii_picture_hook_asm:
pushStack
bl setMiiPictureHook
stw r3, -4 (sp)
popStack
lwz r12, -0x84 (sp)
cmpwi r12, 0
bne default_behave
blr
default_behave:
stwu sp, -0x40 (sp)
.long 0
.long 0
set_mii_picture_hook_asm_end: