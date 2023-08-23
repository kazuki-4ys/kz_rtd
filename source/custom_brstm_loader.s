#include <ppc-asm.h>

.global get_custom_brstm_loader
.global get_custom_brstm_loader_end


get_custom_brstm_loader_end:
    mflr r12
    b get_custom_brstm_loader_end_b
get_custom_brstm_loader:
    mflr r12
bl blTrickCommonEnd
custom_brstm_loader:

#original code by CLF78
#https://mariokartwii.com/showthread.php?tid=1881

# Check if we are loading a track song by checking the file's first character
lbz r3, 0x15C(sp)

cmpwi r3, 'n'
beq+ isTrack

cmpwi r3, 'S'
beq+ isTrack

cmpwi r3, 'r'
bne originalTrack

isTrack:

# Do bl trick
bl trick

# Main format string
.string "%sstrm/%02x_%d%s.brstm"

# Last lap string
.string "_F"
.balign 4

# Set main format string
trick:
mflr r4

# Set root path
addi r5, r29, 0x8

lis r8, 0x8000
lwz r8, 0xCC0 (r8)

lwz r6, 0 (r8)
lwz r7, 4 (r8)

# Set last lap string
addi r8, r4, 0x17

# Load last character of filename before the extension
addi r9, r28, 0x150
lbzx r9, r9, sp

# Check for an F either lower or uppercase
cmpwi r9, 'f'
beq isFast

cmpwi r9, 'F'
beq isFast

# Add two to fast lap string if not fast
addi r8, r8, 2

# String buffer (this part of the stack is no longer used at this point in the function)
isFast:
addi r3, sp, 0x24

# Call sprintf
lis r12, sprintf@h
ori r12, r12, sprintf@l
mtctr r12
bctrl

# Call DVDConvertPathToEntrynum
addi r3, sp, 0x24
lis r12, DVDConvertPathToEntryNum@h
ori r12, r12, DVDConvertPathToEntryNum@l
mtctr r12
bctrl

# Check if file exists
cmpwi r3, -1
beq originalTrack

# It does, we can use this path!
addi r26, sp, 0x24
b end

# Original instruction
originalTrack:
addi r26, sp, 0x150

# Return
end:

.long 0
get_custom_brstm_loader_end_b:
    bl blTrickCommonEnd