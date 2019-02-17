#ifndef WINDOWS_H
#define WINDOWS_H

#include "mainheader.h"
#include "randombool.h"

extern pthread_mutex_t lock;
extern pthread_cond_t con;

void *CtrWindows(void *);
void *CheckDoors(void *);
void *LockAll(void *);

#endif
