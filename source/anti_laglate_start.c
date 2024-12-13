#include "anti_laglate_start.h"

#ifdef RMCP

#define PATCH1_ADDR 0x80533430

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x8052e8e8

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80532db0

#endif

void installAntilagLateStart(void){

    //by Ro
    //https://mariokartwii.com/showthread.php?tid=2318

    injectC2Patch((void*)PATCH1_ADDR, get_anti_laglate_start(), get_anti_laglate_start_end());
}