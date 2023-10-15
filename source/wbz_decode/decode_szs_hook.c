#include "decode_szs_hook.h"
#include "wu8_decode.h"
#include "libbz2/bzlib.h"
#include "liblzma/LzmaDec.h"

#ifdef RMCP

#define PATCH1_ADDR 0x80519530
#define PATCH2_ADDR 0x80519560

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x805150bc
#define PATCH2_ADDR 0x805150ec

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80518eb0
#define PATCH2_ADDR 0x80518ee0

#endif

void dvd_archive_decompress_hook1_asm(void);
void dvd_archive_decompress_hook1_asm_end(void);

void dvd_archive_decompress_hook2_asm(void);
void dvd_archive_decompress_hook2_asm_end(void);

void bz_internal_error(int errcode){
    OSReport("[KZ-RTD]: bz_internal_error errcode = %d\n", errcode);
}

void installDvdArchiveDecompressHook(void){
    injectC2Patch((void*)PATCH1_ADDR, dvd_archive_decompress_hook1_asm, dvd_archive_decompress_hook1_asm_end);
    injectC2Patch((void*)PATCH2_ADDR, dvd_archive_decompress_hook2_asm, dvd_archive_decompress_hook2_asm_end);
}

unsigned int DvdArchiveDecompressHook1(unsigned char *fileStart){
    //replace here.
    //https://github.com/riidefi/mkw/blob/master/source/game/system/DvdArchive.cpp#L222
    if(!memcmp(fileStart, "Yaz0", 4))return EGG__Decomp__getExpandSize(fileStart);
    //Assume that this is wbz.
    unsigned int result;
    memcpy(&result, fileStart + 0xC, 4);
    return result;
}

void decompressBz2(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap);
void decompressLzma(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap);

void DvdArchiveDecompressHook2(unsigned char* mFileStart, unsigned char *archive, unsigned int archiveSize, unsigned int mFileSize, void *heap){
    //replace here.
    //https://github.com/riidefi/mkw/blob/master/source/game/system/DvdArchive.cpp#L224
    if(!memcmp(mFileStart, "Yaz0", 4))EGG__Decomp__decodeSZS(mFileStart, archive);
    if(!memcmp(mFileStart, "WBZa", 4))decompressBz2(mFileStart + 0x10, mFileSize - 0x10, archive, *((unsigned int*)((void*)(mFileStart + 0xC))), heap);
    if(!memcmp(mFileStart, "WLZa", 4))decompressLzma(mFileStart + 0x10, mFileSize - 0x10, archive, *((unsigned int*)((void*)(mFileStart + 0xC))), heap);
    if(!memcmp(archive, "WU8a", 4))decode_wu8(archive, archiveSize, heap);
}

void decompressBz2(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap){
    bzHeap = heap;
    bz_internal_error(BZ2_bzBuffToBuffDecompress((void*)dest, &destSize, (void*)src, srcSize, 0, 4));
}

void *lzmaHeap;

void* my_lzma_malloc(void *p, unsigned int size){
    return my_malloc_from_heap(size, lzmaHeap);
}

void my_lzma_free(void *p, void *ptr){
    Egg__Heap__Free(ptr, lzmaHeap);
}

void decompressLzma(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap){
    lzmaHeap = heap;
    ELzmaStatus status;
    ISzAlloc isza;
    isza.Alloc = (void*)my_lzma_malloc;
    isza.Free = (void*)my_lzma_free;
    srcSize = srcSize - 13;
    int ret = (int)LzmaDecode((Byte*)dest, (SizeT*)(&destSize), (Byte*)(src + 13), (SizeT*)(&srcSize), (Byte*)src, 5, LZMA_FINISH_END, &status, &isza);
    if(ret != SZ_OK)OSReport("[KZ-RTD]: decompressLzma ret = %d\n", ret);
}