#include <ppc-asm.h>

.global get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm
.global get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end

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

get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end:
    mflr r12
    b get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end_b
get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm:
    mflr r12
bl blTrickCommonEnd
extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm:
#もし、UIDvdArchiveが要求されたら代わりにExtraMultiDvdArchiveを返す
#https://github.com/riidefi/mkw/blob/454ba2d115b02af4462dd34b854573909b454722/source/game/system/LocalizedArchive.cpp#L29
    cmpwi r3, 2
    bne extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end
    pushStack
    bl patch1_return_ExtraMultiDvdArchiveInstance
    stw r3, -4 (sp)
    popStack
    lwz r3, -0x84 (sp)
    blr
    extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end:
    stwu sp, -0x10 (sp)
    .long 0
get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end_b:
    bl blTrickCommonEnd