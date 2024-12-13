#include "riivolution_launcher.h"

#ifdef RMCP

#define PATCH1_ADDR 0x80009634

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x800095f4

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80009590

#endif

unsigned char nandIsFileExist(const char *path){
    int fd = ISFS_Open(path, 1);
    if(fd >= 0){
        ISFS_Close(fd);
        return 1;
    }
    return 0;
}

void launchRiivolution(void){
    if(getSceneID() != 0x7A)return;
    if(nandIsFileExist("/title/00010001/52494956/content/title.tmd")){
        OSLaunchTitle(0x0001000152494956);
    }else{
        OSLaunchTitle(0x0000000100000002);
    }
    return;
}

void installRiivolutionLauncher(void){
    injectC2Patch((void*)PATCH1_ADDR, get_riivolution_launcher(), get_riivolution_launcher_end());
}