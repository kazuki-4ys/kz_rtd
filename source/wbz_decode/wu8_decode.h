#ifndef _WU8_DECODE_H_
#define _WU8_DECODE_H_

#include "../common.h"

#define U8_MAGIC 0x55AA382D
#define U8_NODE_SIZE 0xC

typedef struct{
    unsigned char *data;
    unsigned int size;
    void *heap;
}u8_archive_auto_add_get_file_dest;

typedef struct{
    unsigned int magic;
    unsigned int firstNodeOffset;
    unsigned int nodeAndStringTableSize;
    unsigned int fileDataOffset;
}u8_header;

typedef struct{
    unsigned int fileNameOffset;
    unsigned int fileDataOffset;
    unsigned int fileDataLength;
}u8_node;

typedef struct{
    u8_header header;
    unsigned char *nodeAndStringTable;
    DVDFileInfo fi;
    void *heap;
}u8_archive;

void u8_archive_init_auto_add(u8_archive *src, const char *path, void *heap);
void u8_archive_deinit_auto_add(u8_archive *src);
void getFullPath_rec(u8_archive *src, unsigned int targetNodeIndex, char *destPath);
char* u8_get_full_path(u8_archive *src, unsigned int targetNodeIndex, char *pathBuffer);
void u8_archive_get_file_auto_add(u8_archive *src, const char *path, u8_archive_auto_add_get_file_dest *dest);
void decode_wu8(unsigned char *src, unsigned int srcSize, void *heap);

#endif//_WU8_DECODE_H_