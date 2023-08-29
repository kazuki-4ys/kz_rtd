#include "course_cache_load_hook.h"

void *get_course_cache_load_hook_asm_1(void);
void *get_course_cache_load_hook_asm_1_end(void);
void *get_course_cache_load_hook_asm_2(void);
void *get_course_cache_load_hook_asm_2_end(void);

#ifdef RMCP

#define PATCH1_ADDR 0x80541b58
#define PATCH2_ADDR 0x80541bc4

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x8053c61c
#define PATCH2_ADDR 0x8053c688

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x805414d8
#define PATCH2_ADDR 0x80541544

#endif

void installCourseCacheLoadHook(void){
    injectC2Patch((void*)PATCH1_ADDR, get_course_cache_load_hook_asm_1(), get_course_cache_load_hook_asm_1_end());
    injectC2Patch((void*)PATCH2_ADDR, get_course_cache_load_hook_asm_2(), get_course_cache_load_hook_asm_2_end());
}

unsigned char getCourseCacheLoadHook1(void *self, unsigned int slotID){
    //replace here
    //https://github.com/riidefi/mkw/blob/83186fbd1b12a05fc8539f6f0109b1318177778d/source/game/system/ResourceManager.cpp#L812
    if(myGlobalVarPtr->disableCacheLoad)return 0;
    myGlobalVarPtr->courseCache = self;
    if(myGlobalVarPtr->couresCacheloadCountOnline != 0)return 1;
    myGlobalVarPtr->couresCacheloadCountOnline++;
    if(!(myGlobalVarPtr->disableCacheLoad)){
        myGlobalVarPtr->slotID = slotID;
        if(slotID >= COURSE_SLOT_MAX){
            myGlobalVarPtr->determinedTextureHackIndex = 0;
        }else{
            if(myGlobalVarPtr->textureHackCount[slotID] < 2 || (!(myGlobalVarPtr->disableOriginalTracks))){
                myGlobalVarPtr->determinedTextureHackIndex = getRandom(myGlobalVarPtr->textureHackCount[slotID]);
            }else{
                myGlobalVarPtr->determinedTextureHackIndex = getRandom(myGlobalVarPtr->textureHackCount[slotID] - 1) + 1;
            }
        }
        OSReport("[KZ-RTD]: special_slot: %02x\n", myGlobalVarPtr->slotID);
        OSReport("[KZ-RTD]: variation_slot: %d\n", myGlobalVarPtr->determinedTextureHackIndex);
    }
    return 1;
}

void getCourseCacheLoadHook2(char *buffer, unsigned int bufferSize, const char* format, unsigned int slotID){
    //replace here
    //https://github.com/riidefi/mkw/blob/83186fbd1b12a05fc8539f6f0109b1318177778d/source/game/system/ResourceManager.cpp#L823
    if(myGlobalVarPtr->determinedTextureHackIndex == 0){//if it is 0, load nintendo track
        sprintf(buffer, "Race/Course/%s", COURSE_NAMES[slotID]);
    }else{
        sprintf(buffer, "Race/Course/%02x_%d", slotID, myGlobalVarPtr->determinedTextureHackIndex);
    }
}