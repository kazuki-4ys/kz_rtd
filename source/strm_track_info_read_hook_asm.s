#include <ppc-asm.h>

.global get_strm_track_info_read_hook_asm
.global get_strm_track_info_read_hook_asm_end

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

get_strm_track_info_read_hook_asm_end:
    mflr r12
    b get_strm_track_info_read_hook_asm_end_b
get_strm_track_info_read_hook_asm:
    mflr r12
bl blTrickCommonEnd
strm_track_info_read_hook_asm:
    mr r12, r5
    rlwinm  r12, r12, 8, 24, 31
    andi. r12, r12, 0x80
    cmpwi r12, 0x80
    bne not_default_behave
    lis r12, 0x7FFF
    ori r12, r12, 0xFFFF
    and r5, r5, r12
    b skip_all
    not_default_behave:
    pushStack
    bl strmTrackInfoReadHook
    stw r3, -4 (sp)
    popStack
    lwz r3, -0x84 (sp)
    blr
    skip_all:
    stwu sp, -0x20 (sp) #default instruction

    .long 0
get_strm_track_info_read_hook_asm_end_b:
    bl blTrickCommonEnd