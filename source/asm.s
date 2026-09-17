#include <ppc-asm.h>

.global getSystemHeap_p
.global getSystemHeap_e
.global getSystemHeap_j
.global blTrickCommonEnd
.global on_rel_loaded_asm

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

#by vega
#https://mariokartwii.com/showthread.php?tid=1218
getSystemHeap_p:
    lwz r3, -0x5CA0(r13)
    lwz r3, 0x24(r3)
    blr

getSystemHeap_e:
    lwz r3, -0x5CA8(r13)
    lwz r3, 0x24(r3)
    blr

getSystemHeap_j:
    lwz r3, -0x5CA0(r13)
    lwz r3, 0x24(r3)
    blr

blTrickCommonEnd:
    mflr r3
    mtlr r12
    blr

on_rel_loaded_asm:
    pushStack
    bl OnRelLoaded
    popStack
    lwz r26, 0x1C (r29)
    blr