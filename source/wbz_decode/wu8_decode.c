#include "wu8_decode.h"

const char *AUTO_ADD_NOT_FOUND_MSG = "sd:/rk_dumper/auto-add.arc does not exist.\n\nPlease run RevoKart Dumper first.\nhttps://github.com/kazuki-4ys/RevoKart_Dumper/releases\n\n\n\n                                                                                  - kazuki_4ys\n";

#define U8_MAGIC 0x55AA382D

void printAutoAddNotExsistMessage(void){
    unsigned int col = 0xE0E0E0FF;
    unsigned int col2 = 0x003000FF;
    if(*((unsigned char*)((void*)0x80005F27)) == 0x10){
        OSFatal(&col, &col2, auto_add_not_found_msg_jpn_bin);
    }else{
        OSFatal(&col, &col2, AUTO_ADD_NOT_FOUND_MSG);
    }
    return;
}

void u8_archive_init_auto_add(u8_archive *src, const char *path, void *heap){
    src->heap = heap;
    src->nodeAndStringTable = NULL;
    if(!DVDOpen(path, &(src->fi))){
        printAutoAddNotExsistMessage();
        return;
    }
    if(!(src->fi.length)){
        printAutoAddNotExsistMessage();
        return;
    }
    void *tmpHeader = my_malloc_from_heap(0x10, heap);
    DVDReadPrio(&(src->fi), tmpHeader, 0x10, 0, 2);
    memcpy(&(src->header), tmpHeader, 0x10);
    Egg__Heap__Free(tmpHeader, heap);
    src->nodeAndStringTable = my_malloc_from_heap(src->header.nodeAndStringTableSize, heap);
    DVDReadPrio(&(src->fi), src->nodeAndStringTable, src->header.nodeAndStringTableSize, src->header.firstNodeOffset, 2);

    //for test
    /*char *tmpFullPath = my_malloc_from_heap(1024, heap);
    u8_node *firstNode = (void*)(src->nodeAndStringTable);
    u8_node *targetNode = NULL;
    char *fullPath = NULL;
    unsigned int allNodeCount = firstNode->fileDataLength;
    for(unsigned int i = 0;i < allNodeCount;i++){
        if(i == 0)continue;
        targetNode = firstNode + i;
        fullPath = u8_get_full_path(src, i, tmpFullPath);
        OSReport("%s\n", fullPath);
    }
    Egg__Heap__Free(tmpFullPath, src->heap);*/
}

void u8_archive_deinit_auto_add(u8_archive *src){
    if(!src->nodeAndStringTable)return;
    Egg__Heap__Free(src->nodeAndStringTable, src->heap);
    DVDClose(&(src->fi));
}

void getFullPath_rec(u8_archive *src, unsigned int targetNodeIndex, char *destPath){
    unsigned int parentNodeIndex = 0;
    u8_node *firstNode = (void*)(src->nodeAndStringTable);
    u8_node *targetNode = firstNode + targetNodeIndex;
    u8_node *parentNode = NULL;
    unsigned int allNodeCount = firstNode->fileDataLength;
    if((targetNode->fileNameOffset & 0x01000000) == 0x01000000){
        parentNodeIndex = targetNode->fileDataOffset;
        parentNode = firstNode + parentNodeIndex;
    }else{
        parentNodeIndex = targetNodeIndex - 1;
        while(1){
            parentNode = firstNode + parentNodeIndex;
            if((parentNode->fileNameOffset & 0x01000000) == 0x01000000){
                if(parentNode->fileDataLength > targetNodeIndex)break;
            }
            if(!parentNodeIndex)break;
            parentNodeIndex--;
        }
    }
    char *path = src->nodeAndStringTable + (targetNode->fileNameOffset & 0xFFFFFF) + allNodeCount * U8_NODE_SIZE;
    *destPath = '/';
    unsigned int pathLen = strlen(path);
    if((targetNode->fileNameOffset & 0x01000000) == 0x01000000){
        memcpy(destPath - pathLen, path, pathLen);
    }else{
        memcpy(destPath - pathLen + 1, path, pathLen);
    }
    if(!parentNodeIndex)return;
    if((targetNode->fileNameOffset & 0x01000000) == 0x01000000){
        getFullPath_rec(src, parentNodeIndex, destPath - pathLen - 1);
    }else{
        getFullPath_rec(src, parentNodeIndex, destPath - pathLen);
    }
}

char* u8_get_full_path(u8_archive *src, unsigned int targetNodeIndex, char *pathBuffer){
    memset(pathBuffer, 0, 1024);
    if(!targetNodeIndex)return pathBuffer;
    getFullPath_rec(src, targetNodeIndex, pathBuffer + 1022);
    char *fullPath = pathBuffer + 1022;
    while(*(fullPath) != '\0'){
        fullPath--;
    }
    fullPath++;
    return fullPath;
}

unsigned char u8_archive_is_file_exist_auto_add(u8_archive *src, const char *path){
    unsigned char result = 0;
    char *tmpFullPath = my_malloc_from_heap(1024, src->heap);
    u8_node *firstNode = (void*)(src->nodeAndStringTable);
    u8_node *targetNode = NULL;
    char *fullPath = NULL;
    unsigned int allNodeCount = firstNode->fileDataLength;
    for(unsigned int i = 0;i < allNodeCount;i++){
        fullPath = u8_get_full_path(src, i, tmpFullPath);
        if(!strcmp(fullPath, path)){
            result = 1;
            break;
        }
    }
    Egg__Heap__Free(tmpFullPath, src->heap);
    return result;
}

void u8_archive_get_file_auto_add(u8_archive *src, const char *path, u8_archive_auto_add_get_file_dest *dest){
    dest->data = NULL;
    dest->size = 0;
    if(!src->nodeAndStringTable)return;
    char *tmpFullPath = my_malloc_from_heap(1024, src->heap);
    u8_node *firstNode = (void*)(src->nodeAndStringTable);
    u8_node *targetNode = NULL;
    char *fullPath = NULL;
    unsigned int allNodeCount = firstNode->fileDataLength;
    for(unsigned int i = 0;i < allNodeCount;i++){
        if(i == 0)continue;
        targetNode = firstNode + i;
        if((targetNode->fileNameOffset & 0x01000000) == 0x01000000)continue;
        fullPath = u8_get_full_path(src, i, tmpFullPath);
        if(strcmp(fullPath, path))continue;
        Egg__Heap__Free(tmpFullPath, src->heap);
        dest->data = my_malloc_from_heap(targetNode->fileDataLength, src->heap);
        dest->heap = src->heap;
        dest->size = targetNode->fileDataLength;
        unsigned int offset = targetNode->fileDataOffset;
        DVDReadPrio(&(src->fi), dest->data, dest->size, offset, 2);
        return;
    }
    Egg__Heap__Free(tmpFullPath, src->heap);
}

unsigned char getBasickeyBySize(unsigned int srcSize){
    unsigned char tmp[4];
    memcpy(tmp, &srcSize, 4);
    return tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3];
}

void decode_wu8(unsigned char *src, unsigned int srcSize, void *heap){
    //https://wiki.tockdom.com/wiki/WU8_(File_Format)#Algorithm
    u8_archive src_wu8, auto_add;
    char *tmpFullPath = my_malloc_from_heap(1024, heap);
    u8_archive_init_auto_add(&auto_add, "/Race/Course/auto-add.arc", heap);
    //Algorithm 6
    unsigned int tmp = U8_MAGIC;
    memcpy(src, &tmp, 4);
    memcpy(&(src_wu8.header), src, 16);
    src_wu8.nodeAndStringTable = src + src_wu8.header.firstNodeOffset;
    u8_node *firstNode = (void*)src_wu8.nodeAndStringTable;
    //Algorithm 1
    unsigned char basicKey = getBasickeyBySize(srcSize);
    unsigned char summaryKey = basicKey;
    //Algorithm 5
    for(unsigned int i = 0;i < src_wu8.header.nodeAndStringTableSize;i++)src_wu8.nodeAndStringTable[i] = src_wu8.nodeAndStringTable[i] ^ basicKey;
    //Algorithm 2 and 3
    unsigned int allNodeCount = firstNode->fileDataLength;
    for(unsigned int i = 1;i < allNodeCount;i++){
        char *fullPath;
        u8_archive_auto_add_get_file_dest origFile;
        if(((firstNode + i)->fileNameOffset & 0x01000000) == 0x01000000)continue;
        unsigned int fileSize = (firstNode + i)->fileDataLength;
        unsigned char *file = src + (firstNode + i)->fileDataOffset;
        fullPath = u8_get_full_path(&src_wu8, i, tmpFullPath);
        if(!u8_archive_is_file_exist_auto_add(&auto_add, fullPath))continue;
        u8_archive_get_file_auto_add(&auto_add, fullPath, &origFile);
        // Algorithm 3
        //https://github.com/Wiimm/wiimms-szs-tools/blob/336da838ce43edae40dd708dd465f1f43a2c312d/project/src/lib-szs.c#L1795
        summaryKey ^= origFile.data[origFile.size / 2] ^ origFile.data[origFile.size / 3] ^ origFile.data[origFile.size / 4];
        for(unsigned int i = 0;i < fileSize;i++){
            *(file + i) = basicKey ^ (*(file + i)) ^ (*(origFile.data + (i % origFile.size)));
        }
        Egg__Heap__Free(origFile.data, origFile.heap);
    }
    // Algorithm 4
    for(unsigned int i = 1;i < allNodeCount;i++){
        char *fullPath;
        if(((firstNode + i)->fileNameOffset & 0x01000000) == 0x01000000)continue;
        unsigned int fileSize = (firstNode + i)->fileDataLength;
        unsigned char *file = src + (firstNode + i)->fileDataOffset;
        fullPath = u8_get_full_path(&src_wu8, i, tmpFullPath);
        if(u8_archive_is_file_exist_auto_add(&auto_add, fullPath))continue;
        for(unsigned int i = 0;i < fileSize;i++)*(file + i) = summaryKey ^ (*(file + i));
    }
    u8_archive_deinit_auto_add(&auto_add);
    Egg__Heap__Free(tmpFullPath, heap);
}