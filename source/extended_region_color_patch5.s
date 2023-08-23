#include <ppc-asm.h>

.global get_extended_region_color_patch_5
.global get_extended_region_color_patch_5_end


get_extended_region_color_patch_5_end:
    mflr r12
    b get_extended_region_color_patch_5_end_b
get_extended_region_color_patch_5:
    mflr r12
bl blTrickCommonEnd
extended_region_color_patch_5:

#r12 is a color
#r12 = 0xRRGGBB

lis       r12, 0xFFFF
ori       r12, r12, 0xFFFF
lwz       r0, 0x38C(r3)
cmpwi     r0, 0xFF
bne+ not_region_ff
li        r12, 0xFF #r12 = black
b skip_all

not_region_ff:
cmpwi r0, 0xFE
bne+ not_region_fe
lis       r12, 0xF082
ori       r12, r12, 0x28FF#r12 = orange
b skip_all

not_region_fe:
cmpwi r0, 0xFD
bne+ skip_all
lis r12, 0xFF
ori r12, r12, 0xFFFF#r12 = cyan

skip_all:
stw r12, 0x2C(sp)#store region color

.long 0
get_extended_region_color_patch_5_end_b:
    bl blTrickCommonEnd