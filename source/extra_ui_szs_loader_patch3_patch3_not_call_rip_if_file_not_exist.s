#include <ppc-asm.h>

.global get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist
.global get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end

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

.macro call_link address
    lis r12, \address@h
    ori r12, r12, \address@l
    mtlr r12
    blrl
.endm

get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end:
    mflr r12
    b get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end_b
get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist:
    mflr r12
bl blTrickCommonEnd
extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist:
    pushStack
    mr r14, r3
    mr r15, r4
    mr r16, r5
    mr r3, r4
    call_link DVDConvertPathToEntryNum
    cmpwi r3, 0
    blt not_call_rip_file
    mr r3, r14
    mr r4, r15
    mr r5, r16
    li r6, 8
    call_link DvdArchive__ripFile
    not_call_rip_file:
    popStack

    .long 0

get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end_b:
    bl blTrickCommonEnd