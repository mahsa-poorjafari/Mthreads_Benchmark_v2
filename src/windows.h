#ifndef WINDOWS_H
#define WINDOWS_H


extern pthread_mutex_t lock;
extern pthread_cond_t con;

void *CtrWindows(void *);
void *CheckDoors(void *);

#endif
