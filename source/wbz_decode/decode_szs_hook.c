#include "decode_szs_hook.h"
#include "wu8_decode.h"
#include "libbz2/bzlib.h"
#include "liblzma/LzmaDec.h"

#ifdef RMCP

#define PATCH1_ADDR 0x80519530
#define PATCH2_ADDR 0x80218c2c

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x805150bc
#define PATCH2_ADDR 0x80218b8c

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80518eb0
#define PATCH2_ADDR 0x80218b4c

#endif

void dvd_archive_decompress_hook1_asm(void);
void dvd_archive_decompress_hook1_asm_end(void);

void dvd_archive_decompress_hook2_asm(void);
void dvd_archive_decompress_hook2_asm_end(void);

void bz_internal_error(int errcode){
    OSReport("[KZ-RTD]: bz_internal_error errcode = %d\n", errcode);
}

int EGG__Decomp__getExpandSize_Replace(unsigned char *src);

void installDvdArchiveDecompressHook(void){
    injectC2Patch((void*)PATCH1_ADDR, dvd_archive_decompress_hook1_asm, dvd_archive_decompress_hook1_asm_end);
    injectC2Patch((void*)PATCH2_ADDR, dvd_archive_decompress_hook2_asm, dvd_archive_decompress_hook2_asm_end);
    injectC2Patch(EGG__Decomp__getExpandSize, EGG__Decomp__getExpandSize_Replace, NULL);
}

void *decodeSzsHeap;
unsigned int srcSize;

unsigned int DvdArchiveDecompressHook1(unsigned char *fileStart, void *heap, unsigned int sourceSize){
    //replace here.
    //https://github.com/riidefi/mkw/blob/master/source/game/system/DvdArchive.cpp#L222
    decodeSzsHeap = heap;
    if(!memcmp(fileStart, "Yaz0", 4))return EGG__Decomp__getExpandSize(fileStart);
    //Assume that this is wbz or wlz.
    unsigned int result;
    memcpy(&result, fileStart + 0xC, 4);
    srcSize = sourceSize;
    return result;
}

void decompressBz2(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap);
void decompressLzma(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap);

unsigned int DvdArchiveDecompressHook2(unsigned char* src, unsigned char *dest){
    //replace here.
    //https://github.com/riidefi/mkw/blob/40c587abb0bb386532aaf038e290524c86ab4c1f/source/egg/core/eggDecomp.cpp#L35
    if(!memcmp(src, "Yaz0", 4)){
        return 0;
    }
    if(!memcmp(src, "WBZa", 4))decompressBz2(src + 0x10, srcSize - 0x10, dest, *((unsigned int*)((void*)(src + 0xC))), decodeSzsHeap);
    if(!memcmp(src, "WLZa", 4))decompressLzma(src + 0x10, srcSize - 0x10, dest, *((unsigned int*)((void*)(src + 0xC))), decodeSzsHeap);
    if(!memcmp(dest, "WU8a", 4))decode_wu8(dest, *((unsigned int*)((void*)(src + 0xC))), decodeSzsHeap);
    return *((unsigned int*)((void*)(src + 0xC)));
}

void decompressBz2(unsigned char *src, unsigned int srcSize, unsigned char *dest, unsigned int destSize, void *heap){
    bzHeap = heap;
    bz_internal_error(BZ2_bzBuffToBuffDecompress((void*)dest, &destSize, (void*)src, srcSize, 0, 4));
}

int EGG__Decomp__getExpandSize_Replace(unsigned char *src){
    if(!memcmp(src, "Yaz0", 4)){
        return *((unsigned int*)((void*)(src + 4)));
    }
    //Assume that this is wbz or wlz.
    return *((unsigned int*)((void*)(src + 0xC)));
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