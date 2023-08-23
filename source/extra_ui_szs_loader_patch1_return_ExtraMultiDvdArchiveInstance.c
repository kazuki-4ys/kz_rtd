#ifdef RMCJ

#define NEW 0x80229cec
#define STRNCPY 0x80013104
#define SNPRINTF 0x8001185c
#define MEMCPY 0x80005f34
#define MULTI_DVD_ARCHIVE__CT 0x80529eb8
#define MULTI_DVD_ARCHIVE__INIT 0x80529fc8
#define SYSTEM_MANAGER__S_INSTANCE 0x80385980
#define LOCALIZED_SZS 0x808b22e8

#endif

#ifdef RMCE

#define NEW 0x80229a48
#define STRNCPY 0x80012680
#define SNPRINTF 0x80010dd8
#define MEMCPY 0x80005f34
#define MULTI_DVD_ARCHIVE__CT 0x805260c4
#define MULTI_DVD_ARCHIVE__INIT 0x805261d4
#define SYSTEM_MANAGER__S_INSTANCE 0x80381c80
#define LOCALIZED_SZS 0x808aead8

#endif

#ifdef RMCP

#define NEW 0x80229dcc
#define STRNCPY 0x800131e0
#define SNPRINTF 0x80011938
#define MEMCPY 0x80005f34
#define MULTI_DVD_ARCHIVE__CT 0x8052a538
#define MULTI_DVD_ARCHIVE__INIT 0x8052a648
#define SYSTEM_MANAGER__S_INSTANCE 0x80386000
#define LOCALIZED_SZS 0x808B3188

#endif

//#define SAVE_RACE_MULTI_DVD_ARCHIVE_VTABLE 0x800011D4
#define MULTI_DVD_ARCHIVE_VTABLE_SIZE 0x10

//void *get_ExtraMultiDvdArchive__init_hidden(void);

//https://github.com/riidefi/mkw/blob/454ba2d115b02af4462dd34b854573909b454722/source/game/host_system/SystemManager.hpp#L16
typedef struct{
    unsigned char pad0[0x5C];
    unsigned int mLanguage;
    unsigned char pad1[4352 - 0x60];
}SystemManager;

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

//C++の内部仕様に近い仮想関数呼び出し (コードが長くなるので使用しない)
/*void ExtraMultiDvdArchive__init(MultiDvdArchive_Struct *self){
    void *ExtraMultiDvdArchive__init_ptr_from_vtable = *((void**)(((unsigned char*)self->vtable) + 0xC));
    void (*ExtraMultiDvdArchive__init_ptr)(MultiDvdArchive_Struct*) = ExtraMultiDvdArchive__init_ptr_from_vtable;
    ExtraMultiDvdArchive__init_ptr(self);
}*/

void ExtraMultiDvdArchive__init_hidden(MultiDvdArchive_Struct *self){
    void (*snprintf)(char*, unsigned int, const char*, ...) = (void*)SNPRINTF;
    void (*strncpy)(char*, const char*, unsigned int) = (void*)STRNCPY;
    void (*MultiDvdArchive__init)(MultiDvdArchive_Struct*) = (void*)MULTI_DVD_ARCHIVE__INIT;
    MultiDvdArchive__init(self);// /Scene/UI/XXXX.szsをロード
    SystemManager *sInstance = *((SystemManager**)((void*)SYSTEM_MANAGER__S_INSTANCE));
    const char **localized_szs = (const char**)((void*)LOCALIZED_SZS);
    snprintf(self->suffixes[1], 0x80, "%s_Add.szs");// /Scene/UI/XXXX_Add.szsをロード
    strncpy(self->suffixes[2], localized_szs[sInstance->mLanguage], 0x80);// /Scene/UI/XXXX_X.szsをロード
    for(unsigned int i = 0;i < 2;i++)self->kinds[i + 1] = 0;
}

void ExtraMultiDvdArchive__ct(MultiDvdArchive_Struct *self){//ExtraMultiDvdArchiveクラスコンストラクタ
    void* (*new)(unsigned int) = (void*)NEW;
    void (*MultiDvdArchiv__ct)(MultiDvdArchive_Struct*, unsigned int) = (void*)MULTI_DVD_ARCHIVE__CT;
    void (*memcpy)(void*, void*, unsigned int) = (void*)MEMCPY;
    MultiDvdArchiv__ct(self, 3);//スーパークラスコンストラクタ
    /*void **saveVtable = (void**)((void*)SAVE_RACE_MULTI_DVD_ARCHIVE_VTABLE);//仮想関数テーブル取得
    if(!(*saveVtable)){//仮想関数テーブルがないなら新しく作成
        *saveVtable = new(MULTI_DVD_ARCHIVE_VTABLE_SIZE);
        memcpy(*saveVtable, self->vtable, MULTI_DVD_ARCHIVE_VTABLE_SIZE);
        void** init_save = (void**)(((unsigned char*)self->vtable) + 0xC);
        *init_save = get_ExtraMultiDvdArchive__init_hidden();//virtual void init(void)をオーバーライド
    }
    self->vtable = *saveVtable;*/

    //vrtual void init()はコンストラクタ以外で呼ばれないため仮想関数テーブル書き換えは行わない
    //(コードの長さ節約のため)

    //ExtraMultiDvdArchive__init(MultiDvdArchive_Struct *self);
    ExtraMultiDvdArchive__init_hidden(self);
}

MultiDvdArchive_Struct* patch1_return_ExtraMultiDvdArchiveInstance(void){
    void* (*new)(unsigned int) = (void*)NEW;
    MultiDvdArchive_Struct* dest = (MultiDvdArchive_Struct*)new(sizeof(MultiDvdArchive_Struct));
    ExtraMultiDvdArchive__ct(dest);
    return dest;
}