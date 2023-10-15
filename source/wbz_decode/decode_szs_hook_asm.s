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
bl DvdArchiveDecompressHook1
stw r3, -4 (sp)
popStack
lwz r3, -0x84 (sp)
.long 0
.long 0
dvd_archive_decompress_hook1_asm_end:

dvd_archive_decompress_hook2_asm:
pushStack
mr r5, r31
lwz r6, 0x18 (r28)
lwz r7, 0x1C (r28)
#r5 = archiveSize
#r6 = mFileSize
#r7 = heap
bl DvdArchiveDecompressHook2
popStack
.long 0
.long 0
dvd_archive_decompress_hook2_asm_end: