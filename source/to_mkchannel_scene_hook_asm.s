#include <ppc-asm.h>

.global get_to_mkchannel_scene_hook_asm
.global get_to_mkchannel_scene_hook_asm_end

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

get_to_mkchannel_scene_hook_asm_end:
    mflr r12
    b get_to_mkchannel_scene_hook_asm_end_b
get_to_mkchannel_scene_hook_asm:
    mflr r12
bl blTrickCommonEnd
to_mkchannel_scene_hook_asm:

    pushStack
    mr r3, r31
    bl toMkchannelSceneHook
    popStack
    mr r4, r31

    .long 0
get_to_mkchannel_scene_hook_asm_end_b:
    bl blTrickCommonEnd