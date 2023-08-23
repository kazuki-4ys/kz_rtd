#include <ppc-asm.h>

.global get_load_course_hook_asm
.global get_load_course_hook_asm_end

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

get_load_course_hook_asm_end:
    mflr r12
    b get_load_course_hook_asm_end_b
get_load_course_hook_asm:
    mflr r12
bl blTrickCommonEnd
load_course_hook_asm:

	pushStack
    mr r4, r28 #slot id
    mr r5, r30 #is_d_szs
	bl load_course_hook
	popStack
    #defaultInstruction

    .long 0
get_load_course_hook_asm_end_b:
    bl blTrickCommonEnd