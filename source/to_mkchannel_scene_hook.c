#include "to_mkchannel_scene_hook.h"

void *get_to_mkchannel_scene_hook_asm(void);
void *get_to_mkchannel_scene_hook_asm_end(void);

#ifdef RMCP

#define PATCH1_ADDR 0x80837ecc

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x8081ffd4

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80837538

#endif

void installToMkchannelSceneHook(void){
    injectC2Patch((void*)PATCH1_ADDR, get_to_mkchannel_scene_hook_asm(), get_to_mkchannel_scene_hook_asm_end());
}

void toMkchannelSceneHook(int nextSceneID){
    if(nextSceneID != 0x7A)return;
    if(myGlobalVarPtr->riivolutionLaunchTimer < 0)myGlobalVarPtr->riivolutionLaunchTimer = 0;
}