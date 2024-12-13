#include <ppc-asm.h>

.set region, REGION_ID

.global get_anti_laglate_start
.global get_anti_laglate_start_end


get_anti_laglate_start_end:
    mflr r12
    b get_anti_laglate_start_end_b
get_anti_laglate_start:
    mflr r12
bl blTrickCommonEnd
anti_laglate_start:

#by Ro
https://mariokartwii.com/showthread.php?tid=2318


.if    (region == 'E' || region == 'e') # RMCE
    lwz r12, -0x7098(r30)
.elseif (region == 'P' || region == 'p') # RMCP
    lwz r12, 0x28D8(r30)
.elseif (region == 'J' || region == 'j') # RMCJ
    lwz r12, -0x3878(r30)
.else # Invalid Region
        .abort
.endif

lwz r12, 0xB70(r12)
cmpwi r12, 0x7
blt- end
li r3, 0x1

end:
cmpwi r3, 0

.long 0
get_anti_laglate_start_end_b:
    bl blTrickCommonEnd