#include <ppc-asm.h>

.global EGG__SceneManager__createSceneHookAsm
.global myPADRead
.global myPADControlMotor

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

EGG__SceneManager__createSceneHookAsm:
pushStack
lwz r3, 0x18 (r5)
bl EGG__SceneManager__createSceneHook
popStack
lwz r25, 0x18 (r5)
blr

myPADRead:
stw r0, 0x54 (sp)
pushStack
bl usbPADRead
stw r3, -4 (sp)
popStack
lwz r12, -0x84 (sp)
cmpwi r12, 0
beq continue_orig_PADRead
lwz r0, 0x54 (sp)
mtlr r0
addi sp, sp, 80
blr
continue_orig_PADRead:
blr

myPADControlMotor:
stw r0, 0x24 (sp)
pushStack
bl usbPADControlMotor
stw r3, -4 (sp)
popStack
lwz r12, -0x84 (sp)
cmpwi r12, 0
beq continue_orig_PADControlMotor
lwz r0, 0x24 (sp)
mtlr r0
addi sp, sp, 0x20
blr
continue_orig_PADControlMotor:
blr