#ifndef _COMMON_H_
#define _COMMON_H_

#define NULL 0

#define COURSE_SLOT_MAX 42
#define COURSE_PATH_MAX 0x40

typedef struct{
    int slotID;
    int determinedTextureHackIndex;
    void *saveUILayoutControlForSom;
    unsigned char somDigit;
    unsigned char isBrstmMulti;

    //これより上のメンバは弄らないこと(アセンブラソースによりハードコーディングされているため)
    //クソコードでごめんね

    unsigned char useCtgpReplicaSom;
    unsigned char useRandomTexture;
    unsigned char changeRegionColor;
    int textureHackCount[COURSE_SLOT_MAX];
    unsigned int randomNumber;//add 1 pre 1 frame to get random texture hack
    unsigned char regionColor;
    unsigned char disableOriginalTracks;
    unsigned char wiimmfiPatcher;
    unsigned char unlockEverything;
    unsigned char changeMatchMakeRegion;
    unsigned short matchMakeRegion;
    int riivolutionLaunchTimer;
}myGlobalVarStruct;

extern myGlobalVarStruct *myGlobalVarPtr;

void injectC2Patch(void *targetAddr, void *codeStart, void *codeEnd);
void u32ToBytes(unsigned char *mem, unsigned int val);
unsigned int bytesToU32(unsigned char *mem);
void ICInvalidateRange(void *_start, unsigned int length);
void OSReport(const char*, ...);
void memcpy(void*, void*, unsigned int);
int ISFS_Open(const char* path, int flag);
void ISFS_Close(int fd);
void OSLaunchTitle(unsigned long long titleID);
int IOS_Open(const char *path, int flags);
void IOS_Close(int fd);

#endif//_COMMON_H_