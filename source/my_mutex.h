#ifndef _MY_MUTEX_H_
#define _MY_MUTEX_H_

#include "common.h"

extern unsigned int __OSBusClock;

int OSDisableInterrupts(void);
int OSRestoreInterrupts(int state);
void OSSleepTicks(long long);

void SleepMicroseconds(unsigned int time);

typedef struct {
    volatile bool locked;
}MyMutex;

void MyMutex_Init(MyMutex *m);
void MyMutex_Lock(MyMutex *m);
void MyMutex_Unlock(MyMutex *m);

#endif//_MY_MUTEX_H_