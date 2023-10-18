#include <ppc-asm.h>

.global dvd_archive_decompress_hook1_asm
.global dvd_archive_decompress_hook1_asm_end
.global dvd_archive_decompress_hook2_asm
.global dvd_archive_decompress_hook2_asm_end

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

dvd_archive_decompress_hook1_asm:
pushStack
lwz r4, 0x1C (r28)
lwz r5, 0x18 (r28)
#r4 = heap
#r5 = mFileSize
bl DvdArchiveDecompressHook1
stw r3, -4 (sp)
popStack
lwz r3, -0x84 (sp)
.long 0
.long 0
dvd_archive_decompress_hook1_asm_end:

dvd_archive_decompress_hook2_asm:
pushStack
bl DvdArchiveDecompressHook2
stw r3, -4 (sp)
popStack
lwz r12, -0x84 (sp)
cmpwi r12, 0
beq skip_blr
mr r3, r12
blr
skip_blr:
stwu sp, -0x10 (sp)
.long 0
.long 0
dvd_archive_decompress_hook2_asm_end: