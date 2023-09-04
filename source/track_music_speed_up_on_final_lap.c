#include "track_music_speed_up_on_final_lap.h"

void *track_music_speed_up_on_final_lap_hook1(void);
void *track_music_speed_up_on_final_lap_hook1_end(void);
void *track_music_speed_up_on_final_lap_hook2(void);
void *track_music_speed_up_on_final_lap_hook2_end(void);
void *track_music_speed_up_on_final_lap_hook3(void);
void *track_music_speed_up_on_final_lap_hook3_end(void);
void *track_music_speed_up_on_final_lap_hook4(void);
void *track_music_speed_up_on_final_lap_hook4_end(void);
void *track_music_speed_up_on_final_lap_hook5(void);
void *track_music_speed_up_on_final_lap_hook5_end(void);

#ifdef RMCP

#define PATCH1_ADDR 0x8070B2b8
#define PATCH2_ADDR 0x8070b2e4
#define PATCH3_ADDR 0x800a5350
#define PATCH4_ADDR 0x8070b2d4

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x80704914
#define PATCH2_ADDR 0x80704940
#define PATCH3_ADDR 0x800a52B0
#define PATCH4_ADDR 0x80704930

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x8070a924
#define PATCH2_ADDR 0x8070A950
#define PATCH3_ADDR 0x800a5270
#define PATCH4_ADDR 0x8070A940

#endif

void installTrackMusicSpeedUpOnFinalLap(void){
    injectC2Patch((void*)PATCH1_ADDR, track_music_speed_up_on_final_lap_hook1, track_music_speed_up_on_final_lap_hook1_end);
    injectC2Patch((void*)PATCH2_ADDR, track_music_speed_up_on_final_lap_hook2, track_music_speed_up_on_final_lap_hook2_end);
    injectC2Patch((void*)PATCH3_ADDR, track_music_speed_up_on_final_lap_hook3, track_music_speed_up_on_final_lap_hook3_end);
    injectC2Patch((void*)PATCH4_ADDR, track_music_speed_up_on_final_lap_hook4, track_music_speed_up_on_final_lap_hook4_end);
    u32ToBytes((void*)(PATCH4_ADDR + 4), 0x41820028);
    ICInvalidateRange((void*)(PATCH4_ADDR + 4), 4);
    injectC2Patch((void*)(PATCH4_ADDR + 0xC), track_music_speed_up_on_final_lap_hook5, track_music_speed_up_on_final_lap_hook5_end);
}