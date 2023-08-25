#include <ppc-asm.h>

.global get_course_cache_load_hook_asm_1
.global get_course_cache_load_hook_asm_1_end
.global get_course_cache_load_hook_asm_2
.global get_course_cache_load_hook_asm_2_end

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

get_course_cache_load_hook_asm_1_end:
    mflr r12
    b get_course_cache_load_hook_asm_1_end_b
get_course_cache_load_hook_asm_1:
    mflr r12
bl blTrickCommonEnd
course_cache_load_hook_asm_1:
    pushStack
    bl getCourseCacheLoadHook1
    stw r3, -4 (sp)
    popStack
    lwz r12, -0x84 (sp)
    cmpwi r12, 0
    bne not_blr
    blr
    not_blr:
    stwu sp, -0x90 (sp)
    .long 0
get_course_cache_load_hook_asm_1_end_b:
    bl blTrickCommonEnd

get_course_cache_load_hook_asm_2_end:
    mflr r12
    b get_course_cache_load_hook_asm_2_end_b
get_course_cache_load_hook_asm_2:
    mflr r12
bl blTrickCommonEnd
course_cache_load_hook_asm_2:
    pushStack
    bl getCourseCacheLoadHook2
    popStack
    .long 0
get_course_cache_load_hook_asm_2_end_b:
    bl blTrickCommonEnd