#ifndef _COMMON_H_
#define _COMMON_H_

#define NULL 0

#define COURSE_SLOT_MAX 42
#define COURSE_PATH_MAX 0x40

//https://github.com/riidefi/mkw/blob/454ba2d115b02af4462dd34b854573909b454722/source/game/system/MultiDvdArchive.hpp
typedef struct{
    void *vtable;
    void* archives;
    unsigned short archiveCount;
    unsigned char pad0[2];
    unsigned int *fileSizes;
    char **suffixes;
    void** fileStarts;
    unsigned int *kinds;
}MultiDvdArchive_Struct;

//https://github.com/riidefi/mkw/blob/47013193474cc88ef07696cb1037eb5227561a50/source/egg/core/eggDisposer.hpp#L28
typedef struct{
    unsigned char unk0[0x10];
}EGG__Disposer_Struct;//size = 0x10;

//https://github.com/riidefi/mkw/blob/47013193474cc88ef07696cb1037eb5227561a50/source/game/system/ResourceManager.hpp#L204
typedef struct{
    EGG__Disposer_Struct s;
    void* mpBuffer;
    void* mpHeap;
    unsigned int mCourseId;
    unsigned int mState;
    MultiDvdArchive_Struct* mpArchive;
}System__CourseCache_Struct;

typedef struct{
    int slotID;
    int determinedTextureHackIndex;
    void *saveUILayoutControlForSom;
    unsigned char somDigit;
    unsigned char useTrackMusicSpeedUpOnFinalLap;
    unsigned char skipSpeedUp;

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
    unsigned char couresCacheloadCountOnline;
    unsigned char disableCacheLoad;
    unsigned int lastSceneID;
    System__CourseCache_Struct *courseCache;
    void *mem2Heap;
    int padHookInstallTimer;
    unsigned char alreadyInstalledPadHook;
}myGlobalVarStruct;

typedef struct{
    void* unk;
    void* mMEM1ArenaLo;
    void* mMEM1ArenaHi;
    void* mMEM2ArenaLo;
    void* mMEM2ArenaHi;
    unsigned int mMemorySize;
    void* mRootHeapMem1;
    void* mRootHeapMem2; 
}BaseSystem;

typedef struct{
    void* head;
    void* tail;
    unsigned short count;
    unsigned short intrusion_offset;
}nw4r__ut__List;

//https://github.com/riidefi/mkw/blob/7f11b3ce7baf41e54aba301617a99a301feda118/source/egg/core/eggHeap.hpp
typedef struct{
    unsigned char unk[0x28];
    nw4r__ut__List mChildren;
    const char* mName;
}Egg__Heap_Struct;

typedef struct {
    unsigned char _00[0x68 - 0x00];
    unsigned short name[10];
    unsigned char _7c[0x94 - 0x7c];
    unsigned int mii_id;
    unsigned int console_id;
    unsigned char _9c[0xb8 - 0x9c];
}Mii;
//https://github.com/mkw-sp/mkw-sp/blob/623553448a7760825909ed3f0748911751c7124b/payload/game/system/Mii.hh

typedef struct{
    void *vtable;
    Mii **m_miis;
    unsigned char _08[0x98 - 0x08];
}UI__MiiGroup_Struct;
//https://github.com/mkw-sp/mkw-sp/blob/623553448a7760825909ed3f0748911751c7124b/payload/game/ui/MiiGroup.hh

typedef struct{
    unsigned char unk0[0x34];
    unsigned int length;
    //0x38
    unsigned char unk1[4];
    //全部で0x3Cバイト
} DVDFileInfo;

extern myGlobalVarStruct *myGlobalVarPtr;
extern const char** COURSE_NAMES;
extern unsigned char canUseDevUsbVen;

void memcpy(void*, void*, unsigned int);
void* Egg__Heap__Alloc(unsigned int, unsigned int, void*);
void* Egg__Heap__Free(void* ptr, void *heap);
void *my_malloc(unsigned int length);
void *my_malloc_mem2(unsigned int length);
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
void MultiDvdArchive__clear(MultiDvdArchive_Struct *self);
void *Egg__ExpHeap__create(unsigned int, void*, unsigned int);
void *nw4r__ut__List_GetNext(const nw4r__ut__List*, const void*);
void checkUseTrackMusicSpeedUpOnFinalLap(void);
int ISFS_Read(int fd, void *buffer, int length);
void VIResetDimmingCount(void);
void UI__LayoutUIControl__setPicture(void*, char*, char*);
void UI__LayoutUIControl__setMiiPicture(void *self, char *targetPaneName, UI__MiiGroup_Struct *miis, unsigned int playedId, unsigned int r7);
unsigned char UI__LayoutUIControl__hasPictureSourcePane(void *self, const char *pane);
void sprintf(char*, const char*, ...);
int DVDOpen(const char *fileName, DVDFileInfo *fileInfo);
int DVDReadPrio(DVDFileInfo *fileInfo, void *addr, unsigned int length, unsigned int offset, unsigned int prio);
int DVDClose(DVDFileInfo *fileInfo);
void *my_malloc_from_heap(unsigned int length, void *heap);
void *memset(void *s, int c, unsigned int n);
int strlen(const char*);
int strcmp(const char*, const char*);
int memcmp(const void *buf1, const void *buf2, unsigned int count);
unsigned int EGG__Decomp__getExpandSize(unsigned char *fileStart);
void EGG__Decomp__decodeSZS(unsigned char* , unsigned char*);

#endif//_COMMON_H_