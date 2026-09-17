#include <ppc-asm.h>

.global EGG__SceneManager__createSceneHookAsm

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