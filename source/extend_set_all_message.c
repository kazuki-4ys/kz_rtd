#include "extend_set_all_message.h"

#ifdef RMCP

#define PATCH1_ADDR 0x805f8c88
#define PATCH2_ADDR 0x805f8d08
#define PATCH3_ADDR 0x805f8d44
#define PATCH4_ADDR 0x805cddac

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x805d83a4
#define PATCH2_ADDR 0x805d8424
#define PATCH3_ADDR 0x805d8460
#define PATCH4_ADDR 0x805c128c

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x805f8564
#define PATCH2_ADDR 0x805f85e4
#define PATCH3_ADDR 0x805f8620
#define PATCH4_ADDR 0x805cd688

#endif

void installExtendedSetAllMessage(void){

    //by stebler
    //https://mariokartwii.com/showthread.php?tid=1730

    injectC2Patch((void*)PATCH1_ADDR, get_extend_set_all_message_patch1(), get_extend_set_all_message_patch1_end());
    u32ToBytes((void*)PATCH2_ADDR, 0x7C832378);
    u32ToBytes((void*)PATCH3_ADDR, 0x386DBFC4);
    u32ToBytes((void*)PATCH4_ADDR, 0x2C14FFFF);
    u32ToBytes((void*)(PATCH4_ADDR + 4), 0x4082000C);
    ICInvalidateRange((void*)PATCH2_ADDR, 4);
    ICInvalidateRange((void*)PATCH3_ADDR, 4);
    ICInvalidateRange((void*)PATCH4_ADDR, 8);
}