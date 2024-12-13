#include <ppc-asm.h>

.set region, REGION_ID

.global get_riivolution_launcher
.global get_riivolution_launcher_end

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


get_riivolution_launcher_end:
    mflr r12
    b get_riivolution_launcher_end_b
get_riivolution_launcher:
    mflr r12
bl blTrickCommonEnd
riivolution_launcher:
pushStack
bl launchRiivolution
popStack
lbz r0, 0x0051 (r3) #default instruction

.long 0
get_riivolution_launcher_end_b:
    bl blTrickCommonEnd