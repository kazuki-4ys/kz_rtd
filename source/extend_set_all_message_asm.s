#include <ppc-asm.h>

.global get_extend_set_all_message_patch1
.global get_extend_set_all_message_patch1_end


get_extend_set_all_message_patch1_end:
    mflr r12
    b get_extend_set_all_message_patch1_end_b
get_extend_set_all_message_patch1:
    mflr r12
bl blTrickCommonEnd
extend_set_all_message_patch1:

#by stebler
#https://mariokartwii.com/showthread.php?tid=1730

cmpwi r4, 0x0 # check if the message id is a pointer
bge end # is not, we are done

# otherwise return it as a slot
mr r3, r4
blr

end:
lwz r5, 0x10 (r3) # original instruction

.long 0
get_extend_set_all_message_patch1_end_b:
    bl blTrickCommonEnd