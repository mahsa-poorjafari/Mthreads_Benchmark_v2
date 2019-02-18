#ifndef WINDOWS_H
#define WINDOWS_H

#include "mainheader.h"
#include "randombool.h"

extern pthread_mutex_t lock;
extern pthread_cond_t con;
extern pthread_condattr_t cattr;
void *CtrWindows(void *);
void *CheckDoors(void *);
void *OpenAll(void *);
void *powerwindow_PSG_BackL(void *arg);
void *powerwindow_PSG_BackR(void *arg);
void *powerwindow_PSG_Front(void *arg);
void *powerwindow_DRV(void *arg);


#endif
