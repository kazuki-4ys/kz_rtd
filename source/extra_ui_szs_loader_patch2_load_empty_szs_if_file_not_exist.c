#include "empty_szs.h"

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

typedef unsigned char bool;

#define true 1
#define false 0

//https://github.com/riidefi/mkw/blob/454ba2d115b02af4462dd34b854573909b454722/source/game/system/MultiDvdArchive.cpp#L139

int DVDConvertPathToEntryNum(const char*);

bool extra_ui_szs_loader_patch2_load_empty_szs_if_file_not_exist(MultiDvdArchive_Struct *self, unsigned short i, char *fullname, bool defaultKindFile){
    bool kindFile = defaultKindFile;
    if(kindFile && (DVDConvertPathToEntryNum(fullname) < 0)){//ファイルの存在有無チェック
        kindFile = false;
        //ファイルがないとクラッシュするので
        //空のszsを読ませる
        self->fileStarts[i] = empty_szs;
        self->fileSizes[i] = empty_szs_size;
    }
    return kindFile;
}