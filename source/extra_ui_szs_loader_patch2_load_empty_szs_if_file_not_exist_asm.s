#include <ppc-asm.h>

.global get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm
.global get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end

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

get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end:
    mflr r12
    b get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end_b
get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm:
    mflr r12
bl blTrickCommonEnd
extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm:
    pushStack
    mr r3, r25 #this pointer
    #rlwinm r4, r30, 0, 16, 31 (0000ffff)
    .long 0x57c4043e #上記の命令がなぜがエラー吐くので、直接数値でごり押し
    addi r5, sp, 0x88
    mr r6, r23
    bl extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist
    stw r3, -4 (sp)
    popStack
    lwz r23, -0x84 (sp)
    cmpwi r23, 0 #default instruction replace here https://github.com/riidefi/mkw/blob/454ba2d115b02af4462dd34b854573909b454722/source/game/system/MultiDvdArchive.cpp#L139
    .long 0

get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end_b:
    bl blTrickCommonEnd