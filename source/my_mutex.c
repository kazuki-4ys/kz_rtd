#include "my_mutex.h"

void SleepMicroseconds(unsigned int time){
  OSSleepTicks((((long long)time) * ((__OSBusClock / 4) / 1000)));
}

void MyMutex_Init(MyMutex *m){
    m->locked = false;
}

void MyMutex_Lock(MyMutex *m){
    int state = OSDisableInterrupts();
    while(m->locked){
        OSRestoreInterrupts(state);
        SleepMicroseconds(1000);
        state = OSDisableInterrupts();
    }
    m->locked = true;
    OSRestoreInterrupts(state);
}

void MyMutex_Unlock(MyMutex *m){
    int state = OSDisableInterrupts();
    m->locked = false;
    OSRestoreInterrupts(state);
}