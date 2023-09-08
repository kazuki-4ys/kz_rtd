#include "strm_track_info_read_hook.h"

void *get_strm_track_info_read_hook_asm(void);
void *get_strm_track_info_read_hook_asm_end(void);
void read_strm_sound_info_hook_asm(void);
void read_strm_sound_info_hook_asm_end(void);

#ifdef RMCP

#define PATCH1_ADDR 0x800a4fb0
#define PATCH2_ADDR 0x8009ec70

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x800a4f10
#define PATCH2_ADDR 0x8009ebd0

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x800a4ed0
#define PATCH2_ADDR 0x8009EB90

#endif

void installStrmTrackInfoReadHook(void){
    injectC2Patch((void*)PATCH1_ADDR, get_strm_track_info_read_hook_asm(), get_strm_track_info_read_hook_asm_end());
    u32ToBytes((void*)PATCH2_ADDR, 0x38000000);//li r0, 0
    ICInvalidateRange(PATCH2_ADDR, 4);
}

unsigned int strmTrackInfoReadHook(void *self, void *soundInfo, unsigned int trackId){
    //the code from mkw-sp
    //https://github.com/mkw-sp/mkw-sp/blob/debb1843a084c3a7a958c96d2348ce08ed86764e/payload/nw4r/snd/StrmFileReader.cc#L5
    //by stebler

    unsigned int (*nw4r__snd__StrmFileReader__readStrmTrackInfo)(void*, void*, unsigned int) = (void*)PATCH1_ADDR;
    if(nw4r__snd__StrmFileReader__readStrmTrackInfo(self, soundInfo, 0x80000000 | trackId)){
        return 1;
    }
    return nw4r__snd__StrmFileReader__readStrmTrackInfo(self, soundInfo, 0x80000000);
}