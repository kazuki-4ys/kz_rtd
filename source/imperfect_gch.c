#include "imperfect_gch.h"

//超不完全はコードハンドラ
//Payload_J.binに埋め込んだあるものとは全くの別物(あっちはほぼ完璧)
void ImperfectGch(const char *gct){
    int curLine = 1;
    while(1){
        unsigned char codeType = gct[curLine * 8];
        unsigned int targetAddr = 0;
        switch(codeType){
            case 0x00:
                targetAddr = (bytesToU32(gct + curLine * 8) & 0x00FFFFFF) | 0x80000000;
                *((unsigned char*)((void*)targetAddr)) = *(gct + curLine * 8 + 7);
                ICInvalidateRange((void*)targetAddr, 1);
                curLine++;
                break;
            case 0x02:
                targetAddr = (bytesToU32(gct + curLine * 8) & 0x00FFFFFF) | 0x80000000;
                *((unsigned char*)((void*)targetAddr)) = *(gct + curLine * 8 + 6);
                *((unsigned char*)((void*)(targetAddr + 1))) = *(gct + curLine * 8 + 7);
                ICInvalidateRange((void*)targetAddr, 2);
                curLine++;
                break;
            case 0x04:
                targetAddr = (bytesToU32(gct + curLine * 8) & 0x00FFFFFF) | 0x80000000;
                u32ToBytes((void*)targetAddr, bytesToU32(gct + curLine * 8 + 4));
                ICInvalidateRange((void*)targetAddr, 4);
                curLine++;
                break;
            case 0x06:
                unsigned int charCount = bytesToU32(gct + curLine * 8 + 4);
                targetAddr = (bytesToU32(gct + curLine * 8) & 0x00FFFFFF) | 0x80000000;
                memcpy((void*)targetAddr, gct + (curLine + 1) * 8, charCount);
                ICInvalidateRange((void*)targetAddr, charCount);
                curLine++;
                curLine += charCount / 8;
                if(charCount & 7){
                    curLine++;
                }
                break;
            case 0xC2:
                void *codeStart = (void*)(gct + (curLine + 1) * 8);
                void *codeEnd = (void*)(gct + (curLine + 1 + bytesToU32(gct + curLine * 8 + 4)) * 8);
                void *injectAddr = (void*)((bytesToU32(gct + curLine * 8) & 0x00FFFFFF) | 0x80000000);
                injectC2Patch(injectAddr, codeStart, codeEnd + 4);
                curLine += (bytesToU32(gct + curLine * 8 + 4) + 1);
                break;
            case 0xF0://gct終了
                return;
                break;
            default:
                OSReport("[KZ-RTD]: Warnning!! unknown code type: %02X at line %d\n", codeType, curLine);
                curLine++;
        }
    }
}