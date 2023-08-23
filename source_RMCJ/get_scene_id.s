#include <ppc-asm.h>

.set region, 'J'

.if    (region == 'E' || region == 'e') # RMCE
         .set menu_pointer, 0x809CD508
.elseif (region == 'P' || region == 'p') # RMCP
        .set menu_pointer, 0x809C1E38
.elseif (region == 'J' || region == 'j') # RMCJ
        .set menu_pointer, 0x809C0E98
.else # Invalid Region
        .abort
.endif

.global getSceneID

getSceneID:
    lis r3,menu_pointer@h
    lwz r3,menu_pointer@l (r3)
    cmpwi r3,0
    beq- skip_all
    lwz r3,0(r3)
    cmpwi r3,0
    beq- skip_all
    lwz r3,0(r3)
    skip_all:
    blr