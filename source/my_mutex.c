#include "my_mutex.h"

void SleepMicroseconds(unsigned int time){
  OSSleepTicks((((long long)time) * ((__OSBusClock / 4) / 1000)));
}

void MyMutex_Init(MyMutex *m){
    m->locked = false;
}

void MyMutex_Lock(MyMutex *m){
    while(1){
        int state = OSDisableInterrupts();
        if(m->locked){
            OSRestoreInterrupts(state);
            SleepMicroseconds(1000);
            continue;
        }
        m->locked = true;
        OSRestoreInterrupts(state);
        break;
    }
}

void MyMutex_Unlock(MyMutex *m){
    int state = OSDisableInterrupts();
    m->locked = false;
    OSRestoreInterrupts(state);
}