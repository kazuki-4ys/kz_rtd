#include "common.h"
#include "extend_set_all_message.h"
#include "ctgp_som_replica.h"
#include "imperfect_gch.h"
#include "wiimmfi_gct.h"
#include "exception_handler_gct.h"
#include "change_character_gct.h"
#include "to_mkchannel_scene_hook.h"
#include "strm_track_info_read_hook.h"

#ifdef RMCP

#define RUN_1FR_HOOK 0x8016eac8
#define CUSTOM_BRSTM_LOADER_PATCH_ADDR 0x8009e0bc
#define LOAD_COURSE_PATCH1_ADDR 0x805407f8
#define LOAD_COURSE_PATCH2_ADDR 0x80540844
#define LOAD_COURSE_PATCH3_ADDR 0x80540870
#define DISABLE_COURSE_CACHE_LOADER_ADDR 0x80541b58
#define ORIGINAL_TRACK_NAME_TABLE 0x808b2d4c
#define EXTENDED_REGION_COLOR_PATCH1_ADDR 0x8060a2b4
#define EXTENDED_REGION_COLOR_PATCH2_ADDR 0x8060a2b8
#define EXTENDED_REGION_COLOR_PATCH3_ADDR 0x806513e4
#define EXTENDED_REGION_COLOR_PATCH4_ADDR 0x806513e8
#define EXTENDED_REGION_COLOR_PATCH5_ADDR 0x807f01fc
#define AUTO_BRSAR_PATCH_ADDR 0x80091350
#define REGION_DISMATCH_DATA_RESET_ADDR 0x80544928
#define CHANGE_REGION_COLOR_ADDR 0x8042ab67
#define EXTRA_UI_SZS_LOADER_PATCH1_ADDR 0x8052a098
#define EXTRA_UI_SZS_LOADER_PATCH2_ADDR 0x8052a9fc
#define EXTRA_UI_SZS_LOADER_PATCH3_ADDR 0x8052ac14
#define UNLOCK_EVERY_THING_ADDR 0x80549974

#define MATCH_MAKE_REGION_ADDR_1 0x80653644
#define MATCH_MAKE_REGION_ADDR_2 0x806536b0
#define MATCH_MAKE_REGION_ADDR_3 0x8065920c
#define MATCH_MAKE_REGION_ADDR_4 0x80659260
#define MATCH_MAKE_REGION_ADDR_5 0x80659724
#define MATCH_MAKE_REGION_ADDR_6 0x80659778
#define MATCH_MAKE_REGION_ADDR_7 0x8065a034
#define MATCH_MAKE_REGION_ADDR_8 0x8065a080

#define DISABLE_TT_SAVE_ADDR 0x8054913C

#endif

#ifdef RMCE

#define RUN_1FR_HOOK 0x8016ea28
#define CUSTOM_BRSTM_LOADER_PATCH_ADDR 0x8009e01c
#define LOAD_COURSE_PATCH1_ADDR 0x8053b2bc
#define LOAD_COURSE_PATCH2_ADDR 0x8053b308
#define LOAD_COURSE_PATCH3_ADDR 0x8053b334
#define DISABLE_COURSE_CACHE_LOADER_ADDR 0x8053c61c
#define ORIGINAL_TRACK_NAME_TABLE 0x808ae69c
#define EXTENDED_REGION_COLOR_PATCH1_ADDR 0x805e59e0
#define EXTENDED_REGION_COLOR_PATCH2_ADDR 0x805e59e4
#define EXTENDED_REGION_COLOR_PATCH3_ADDR 0x8061e0d0
#define EXTENDED_REGION_COLOR_PATCH4_ADDR 0x8061e0d4
#define EXTENDED_REGION_COLOR_PATCH5_ADDR 0x807e5bd4
#define AUTO_BRSAR_PATCH_ADDR 0x800912b0
#define REGION_DISMATCH_DATA_RESET_ADDR 0x8053f3ec
#define CHANGE_REGION_COLOR_ADDR 0x804267e7
#define EXTRA_UI_SZS_LOADER_PATCH1_ADDR 0x80525c24
#define EXTRA_UI_SZS_LOADER_PATCH2_ADDR 0x80526588
#define EXTRA_UI_SZS_LOADER_PATCH3_ADDR 0x805267a0
#define UNLOCK_EVERY_THING_ADDR 0x80544438

#define MATCH_MAKE_REGION_ADDR_1 0x8064f1bc
#define MATCH_MAKE_REGION_ADDR_2 0x8064f228
#define MATCH_MAKE_REGION_ADDR_3 0x80654d84
#define MATCH_MAKE_REGION_ADDR_4 0x80654dd8
#define MATCH_MAKE_REGION_ADDR_5 0x8065529c
#define MATCH_MAKE_REGION_ADDR_6 0x806552f0
#define MATCH_MAKE_REGION_ADDR_7 0x80655bac
#define MATCH_MAKE_REGION_ADDR_8 0x80655bf8

#define DISABLE_TT_SAVE_ADDR 0x80543C00

#endif

#ifdef RMCJ

#define RUN_1FR_HOOK 0x8016e9E8
#define CUSTOM_BRSTM_LOADER_PATCH_ADDR 0x8009DFDC
#define LOAD_COURSE_PATCH1_ADDR 0x80540178
#define LOAD_COURSE_PATCH2_ADDR 0x805401C4
#define LOAD_COURSE_PATCH3_ADDR 0x805401F0
#define DISABLE_COURSE_CACHE_LOADER_ADDR 0x805414d8
#define ORIGINAL_TRACK_NAME_TABLE 0x808b2ae4
#define EXTENDED_REGION_COLOR_PATCH1_ADDR 0x80609a28
#define EXTENDED_REGION_COLOR_PATCH2_ADDR 0x80609a2C
#define EXTENDED_REGION_COLOR_PATCH3_ADDR 0x80650a50
#define EXTENDED_REGION_COLOR_PATCH4_ADDR 0x80650a54
#define EXTENDED_REGION_COLOR_PATCH5_ADDR 0x807ef868
#define AUTO_BRSAR_PATCH_ADDR 0x80091270
#define REGION_DISMATCH_DATA_RESET_ADDR 0x805442A8
#define CHANGE_REGION_COLOR_ADDR 0x8042A4E7
#define EXTRA_UI_SZS_LOADER_PATCH1_ADDR 0x80529a18
#define EXTRA_UI_SZS_LOADER_PATCH2_ADDR 0x8052a37c
#define EXTRA_UI_SZS_LOADER_PATCH3_ADDR 0x8052A594
#define UNLOCK_EVERY_THING_ADDR 0x805492F4

#define MATCH_MAKE_REGION_ADDR_1 0x80652CB0
#define MATCH_MAKE_REGION_ADDR_2 0x80652D1C
#define MATCH_MAKE_REGION_ADDR_3 0x80658878
#define MATCH_MAKE_REGION_ADDR_4 0x806588CC
#define MATCH_MAKE_REGION_ADDR_5 0x80658D90
#define MATCH_MAKE_REGION_ADDR_6 0x80658DE4
#define MATCH_MAKE_REGION_ADDR_7 0x806596A0
#define MATCH_MAKE_REGION_ADDR_8 0x806596EC

#define DISABLE_TT_SAVE_ADDR 0x80548ABC

#endif

const char *texture_hack_course_base_path_with_szs = "/Race/Course/%02x_%d.szs";
const char *texture_hack_course_base_d_path_with_szs = "/Race/Course/%02x_%d_d.szs";
const char *texture_hack_course_base_path = "/Race/Course/%02x_%d";
const char *texture_hack_course_base_d_path = "/Race/Course/%02x_%d_d";
const char *original_course_base_path = "Race/Course/%s";
const char *original_course_base_d_path = "Race/Course/%s_d";

const char** COURSE_NAMES = (void*)ORIGINAL_TRACK_NAME_TABLE;

myGlobalVarStruct *myGlobalVarPtr;

void* getSystemHeap_e(void);
void* getSystemHeap_p(void);
void* getSystemHeap_j(void);
void* Egg__Heap__Alloc(unsigned int, unsigned int, void*);
void ICInvalidateRangeAsm(void*, unsigned int);
int DVDConvertPathToEntryNum(const char*);
void strncpy(char*, const char*, unsigned int);
int strlen(const char*);
int strcmp(const char*, const char*);
void sprintf(char*, const char*, ...);
unsigned int NETCalcCRC32(void*, unsigned int);
void *getRacedata(void);
int getSceneID(void);

void *get_run_1fr_asm(void);
void *get_run_1fr_asm_end(void);
void *get_custom_brstm_loader(void);
void *get_custom_brstm_loader_end(void);
void *get_load_course_hook_asm(void);
void *get_load_course_hook_asm_end(void);
void *get_extended_region_color_patch_5(void);
void *get_extended_region_color_patch_5_end(void);
void *get_auto_brsar_patch_asm(void);
void *get_auto_brsar_patch_asm_end(void);
void *get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm(void);
void *get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end(void);
void *get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm(void);
void *get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end(void);
void *get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist(void);
void *get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end(void);

void *my_malloc(unsigned int length){
    unsigned int requsetLength = length;
    if(requsetLength & 0x1F){//0x20でアラインメント alignment for 0x20
        requsetLength = ((requsetLength >> 5) + 1) << 5;
    }
    #ifdef RMCE
    void *systemHeap = getSystemHeap_e();
    #endif
    #ifdef RMCJ
    void *systemHeap = getSystemHeap_j();
    #endif
    #ifdef RMCP
    void *systemHeap = getSystemHeap_p();
    #endif
    return Egg__Heap__Alloc(requsetLength, 0x20, systemHeap);
}

void u32ToBytes(unsigned char *mem, unsigned int val){
    *mem = (val >> 24);
    *(mem + 1) = ((val >> 16) & 0xFF);
    *(mem + 2) = ((val >> 8) & 0xFF);
    *(mem + 3) = (val & 0xFF);
}

unsigned int bytesToU32(unsigned char *mem){
    return (*mem << 24) | (*(mem + 1) << 16) | (*(mem + 2) << 8) | *(mem + 3);
}

void ICInvalidateRange(void *_start, unsigned int length){
    //CPUのキャッシュメモリを更新し、過去にキャッシュされたコードの実行を防ぐ？
    //_start とlengthを0x20でアラインメント alignment for 0x20
    unsigned int start = (unsigned int)_start;
    unsigned int end = start + length;
    if(end & 0x1F){
        end = ((end >> 5) + 1) << 5;
    }
    if(start & 0x1F){
        start = (start >> 5) << 5;
    }
    ICInvalidateRangeAsm((void*)start, end - start);
}

unsigned int makeBranchInstructionByAddrDelta(int addrDelta){//アドレス差分からbranch命令作成
    unsigned int instruction = 0;
    if(addrDelta < 0){
        instruction = addrDelta + 0x4000000;
    }else{
        instruction = addrDelta;
    }
    instruction |= 0x48000000;
    return instruction;
}

void injectBranch(void *target, void *src){
    //srcからtargetへジャンプ
    //branch to src from target
    unsigned int instruction = makeBranchInstructionByAddrDelta((int)target - (int)src);
    u32ToBytes((void*)src, instruction);
    ICInvalidateRange((void*)src, 4);
}

void injectC2Patch(void *targetAddr, void *codeStart, void *codeEnd){
    //inject code like C2 code type
    u32ToBytes((unsigned char*)codeEnd - 8, makeBranchInstructionByAddrDelta((unsigned int)targetAddr + 4 - ((unsigned int)codeEnd - 8)));
    u32ToBytes(targetAddr, makeBranchInstructionByAddrDelta(codeStart - targetAddr));
    ICInvalidateRange((void*)((unsigned int)codeEnd - 8), 4);
    ICInvalidateRange(targetAddr, 4);
}

void installExtendedRegionColor(){
    u32ToBytes((void*)EXTENDED_REGION_COLOR_PATCH1_ADDR, 0x60000000);
    u32ToBytes((void*)EXTENDED_REGION_COLOR_PATCH2_ADDR, 0x60000000);
    u32ToBytes((void*)EXTENDED_REGION_COLOR_PATCH3_ADDR, 0x60000000);
    u32ToBytes((void*)EXTENDED_REGION_COLOR_PATCH4_ADDR, 0x60000000);
    ICInvalidateRange((void*)EXTENDED_REGION_COLOR_PATCH1_ADDR, 4);
    ICInvalidateRange((void*)EXTENDED_REGION_COLOR_PATCH2_ADDR, 4);
    ICInvalidateRange((void*)EXTENDED_REGION_COLOR_PATCH3_ADDR, 4);
    ICInvalidateRange((void*)EXTENDED_REGION_COLOR_PATCH4_ADDR, 4);
    injectC2Patch((void*)EXTENDED_REGION_COLOR_PATCH5_ADDR, get_extended_region_color_patch_5(), get_extended_region_color_patch_5_end());
}

void installExtraUISzsLoader(){
    injectC2Patch((void*)EXTRA_UI_SZS_LOADER_PATCH1_ADDR, get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm(), get_extra_ui_szs_loader_patch1_return_ExtraMultiDvdArchiveInstance_asm_end());
    injectC2Patch((void*)EXTRA_UI_SZS_LOADER_PATCH2_ADDR, get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm(), get_extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist_asm_end());
    injectC2Patch((void*)EXTRA_UI_SZS_LOADER_PATCH3_ADDR, get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist(), get_extra_ui_szs_loader_patch3_patch3_not_call_rip_if_file_not_exist_end());
}

int getTextureHackCountForSlot(unsigned char courseSlot){
    int count = 1;
    char courseName[COURSE_PATH_MAX];
    while(1){
        sprintf(courseName, texture_hack_course_base_path_with_szs, courseSlot, count);
        if(DVDConvertPathToEntryNum(courseName) < 0)return count;
        count++;
    }
    return 0;
}

void installRandomTexture(void){
    //For each slot, find out the number of texture hacks
    for(int i = 0;i < COURSE_SLOT_MAX;i++){
        myGlobalVarPtr->textureHackCount[i] = getTextureHackCountForSlot(i);
    }


    u32ToBytes((void*)LOAD_COURSE_PATCH1_ADDR, 0x48000048);//skip this b 0x48;
    //https://github.com/riidefi/mkw/blob/83186fbd1b12a05fc8539f6f0109b1318177778d/source/game/system/ResourceManager.cpp#L404
    ICInvalidateRange((void*)LOAD_COURSE_PATCH1_ADDR, 4);

    //https://github.com/riidefi/mkw/blob/83186fbd1b12a05fc8539f6f0109b1318177778d/source/game/system/ResourceManager.cpp#L411
    u32ToBytes((void*)LOAD_COURSE_PATCH2_ADDR, 0x60000000);//nop
    ICInvalidateRange((void*)LOAD_COURSE_PATCH2_ADDR, 4);
    injectC2Patch((void*)LOAD_COURSE_PATCH3_ADDR, get_load_course_hook_asm(), get_load_course_hook_asm_end());
    
    //https://github.com/riidefi/mkw/blob/83186fbd1b12a05fc8539f6f0109b1318177778d/source/game/system/ResourceManager.cpp#L812C6-L812C17
    u32ToBytes((void*)DISABLE_COURSE_CACHE_LOADER_ADDR, 0x4e800020);//blr disable course cache load
    ICInvalidateRange((void*)DISABLE_COURSE_CACHE_LOADER_ADDR, 4);
    injectC2Patch((void*)CUSTOM_BRSTM_LOADER_PATCH_ADDR, get_custom_brstm_loader(), get_custom_brstm_loader_end());
}

void installWiimmfiPatcher(void){
    //by Leseratte
    //https://mariokartwii.com/showthread.php?tid=1607
    ImperfectGch(wiimmfi_gct);
}

void installChangeCharacterAndVehicleInBetweenRacesOnline(void){
    //by MrBean 35000vr
    //https://mariokartwii.com/showthread.php?tid=785
    ImperfectGch(change_character_gct);
}

void patchMatchMakeRegion(void){
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_1, 0x38a00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_1, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_2, 0x38c00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_2, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_3, 0x38e00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_3, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_4, 0x38e00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_4, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_5, 0x38e00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_5, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_6, 0x38e00000 | myGlobalVarPtr->matchMakeRegion);
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_6, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_7, 0x38800000 | (myGlobalVarPtr->matchMakeRegion & 0xFF));
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_7, 4);
    u32ToBytes((void*)MATCH_MAKE_REGION_ADDR_8, 0x38800000 | (myGlobalVarPtr->matchMakeRegion & 0xFF));
    ICInvalidateRange((void*)MATCH_MAKE_REGION_ADDR_8, 4);
}

void applyRiivolutionFlags(void){
    myGlobalVarPtr->changeRegionColor = *((unsigned char*)((void*)0x80000CCB));
    myGlobalVarPtr->regionColor = *((unsigned char*)((void*)0x80000CCC));
    myGlobalVarPtr->useCtgpReplicaSom = *((unsigned char*)((void*)0x80000CC7));
    myGlobalVarPtr->somDigit = *((unsigned char*)((void*)0x80000CC8));
    myGlobalVarPtr->wiimmfiPatcher = *((unsigned char*)((void*)0x80000CC6));
    myGlobalVarPtr->unlockEverything = *((unsigned char*)((void*)0x80000CC9));
    myGlobalVarPtr->useRandomTexture = *((unsigned char*)((void*)0x80000CC4));
    myGlobalVarPtr->disableOriginalTracks = *((unsigned char*)((void*)0x80000CC5));
    myGlobalVarPtr->changeMatchMakeRegion = *((unsigned char*)((void*)0x80000CCF));
    if(myGlobalVarPtr->changeMatchMakeRegion){
        myGlobalVarPtr->matchMakeRegion = *((unsigned char*)((void*)0x80000CD0)) * 256;
        myGlobalVarPtr->matchMakeRegion += *((unsigned char*)((void*)0x80000CD1));
    }
}

//基本的にはデバッグ用
void setFlagsForNonRiivolution(void){
    myGlobalVarPtr->changeRegionColor = 1;
    myGlobalVarPtr->regionColor = 5;
    myGlobalVarPtr->useCtgpReplicaSom = 1;
    myGlobalVarPtr->somDigit = 0;
    myGlobalVarPtr->wiimmfiPatcher = 1;
    myGlobalVarPtr->unlockEverything = 1;
    myGlobalVarPtr->useRandomTexture = 1;
    myGlobalVarPtr->disableOriginalTracks = 1;
    myGlobalVarPtr->changeMatchMakeRegion = 1;
    if(myGlobalVarPtr->changeMatchMakeRegion){
        myGlobalVarPtr->matchMakeRegion = 1;
    }
}

/*unsigned char isDolphin(void){
    int fd = IOS_Open("/dev/dolphin", 0);
    if(fd >= 0){
        IOS_Close(fd);
        return 1;
    }
    return 0;
}*/

/*unsigned char isInOnlineRace(void){
    int sceneID = getSceneID();
    //https://wiki.tockdom.com/wiki/List_of_Identifiers
    if(sceneID < 0x68)return 0;
    if(sceneID > 0x76)return 0;
    return 1;
}*/

/*unsigned char isInTitleScreen(void){
    int sceneID = getSceneID();
    //https://wiki.tockdom.com/wiki/List_of_Identifiers
    if(sceneID < 0x3F)return 0;
    if(sceneID > 0x43)return 0;
    return 1;
}*/

void __main(void){
    ImperfectGch(exception_handler_gct);
    if(!myGlobalVarPtr){//allocate memory for our global variables
        myGlobalVarPtr = my_malloc(sizeof(myGlobalVarStruct));
    }

    myGlobalVarPtr->riivolutionLaunchTimer = -1;

    unsigned char defaultRegion = *((unsigned char*)((void*)CHANGE_REGION_COLOR_ADDR));

    applyRiivolutionFlags();
    //setFlagsForNonRiivolution();
    if(!(myGlobalVarPtr->changeMatchMakeRegion))myGlobalVarPtr->matchMakeRegion = defaultRegion;

    injectC2Patch((void*)RUN_1FR_HOOK, get_run_1fr_asm(), get_run_1fr_asm_end());

    installToMkchannelSceneHook();
    installStrmTrackInfoReadHook();

    //by mdmwii
    //https://mariokartwii.com/showthread.php?tid=349
    u32ToBytes((void*)DISABLE_TT_SAVE_ADDR, 0x60000000);
    ICInvalidateRange((void*)DISABLE_TT_SAVE_ADDR, 4);

    //by vega
    //https://mariokartwii.com/showthread.php?tid=1056
    u32ToBytes((void*)REGION_DISMATCH_DATA_RESET_ADDR, 0x7C601B78);
    ICInvalidateRange((void*)REGION_DISMATCH_DATA_RESET_ADDR, 4);

    if(myGlobalVarPtr->changeRegionColor){
        //by anarion
        //https://mariokartwii.com/showthread.php?tid=93
        *((unsigned char*)((void*)CHANGE_REGION_COLOR_ADDR)) = myGlobalVarPtr->regionColor;
    }

    installExtraUISzsLoader();
    installExtendedSetAllMessage();
    injectC2Patch((void*)AUTO_BRSAR_PATCH_ADDR, get_auto_brsar_patch_asm(), get_auto_brsar_patch_asm_end());
    installExtendedRegionColor();
    installChangeCharacterAndVehicleInBetweenRacesOnline();
    if(myGlobalVarPtr->useRandomTexture)installRandomTexture();
    if(myGlobalVarPtr->useCtgpReplicaSom)installCtgpSomReplica();
    if(myGlobalVarPtr->wiimmfiPatcher)installWiimmfiPatcher();
    if(myGlobalVarPtr->unlockEverything){
        //by _tz
        //https://mariokartwii.com/showthread.php?tid=1736
        u32ToBytes((void*)UNLOCK_EVERY_THING_ADDR, 0x38600001);
        ICInvalidateRange((void*)UNLOCK_EVERY_THING_ADDR, 4);
    }
}

unsigned char nandIsFileExist(const char *path){
    int fd = ISFS_Open(path, 1);
    if(fd >= 0){
        ISFS_Close(fd);
        return 1;
    }
    return 0;
}

void launchRiivolution(void){
    if(nandIsFileExist("/title/00010001/52494956/content/title.tmd")){
        OSLaunchTitle(0x0001000152494956);
    }else{
        OSLaunchTitle(0x0000000100000002);
    }
    //OSLaunchTitle(0x0000000100000002);
}

void run_1fr(void){
    if(!myGlobalVarPtr)return;
    myGlobalVarPtr->randomNumber++;
    if(getSceneID())patchMatchMakeRegion();
    if(myGlobalVarPtr->riivolutionLaunchTimer >= 476)launchRiivolution();
    if(myGlobalVarPtr->riivolutionLaunchTimer >= 0)myGlobalVarPtr->riivolutionLaunchTimer++;
    //Wiimmfiの謎パッチにより、リージョンカラーを変更すると国内マッチリージョンまで変わるので毎フレームパッチしてそれを無効化する
}

int getRandom(int max_plus_1){
    //get random number using crc32
    if(!myGlobalVarPtr)return 0;
    if(!max_plus_1)return 0;
    return NETCalcCRC32((void*)(&(myGlobalVarPtr->randomNumber)), 4) % max_plus_1;
}

void load_course_hook(char *dest, unsigned int slotID, unsigned int is_d_szs){
    //dest = buffer to write szs path
    if(!myGlobalVarPtr)return;
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
    if(myGlobalVarPtr->determinedTextureHackIndex == 0){//if it is 0, load nintendo track
        if(is_d_szs){
            sprintf(dest, original_course_base_d_path, COURSE_NAMES[slotID]);
        }else{
            sprintf(dest, original_course_base_path, COURSE_NAMES[slotID]);
        }
    }else{
        if(is_d_szs){
            sprintf(dest, texture_hack_course_base_d_path_with_szs, slotID, myGlobalVarPtr->determinedTextureHackIndex);
            if(DVDConvertPathToEntryNum(dest) < 0){//if _d.szs does not exist, we use normal szs
                sprintf(dest, texture_hack_course_base_path, slotID, myGlobalVarPtr->determinedTextureHackIndex);
            }else{
                sprintf(dest, texture_hack_course_base_d_path, slotID, myGlobalVarPtr->determinedTextureHackIndex);
            }
        }else{
            sprintf(dest, texture_hack_course_base_path, slotID, myGlobalVarPtr->determinedTextureHackIndex);
        }
    }
}