/*
 * windowsup.h
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */

#ifndef WINDOWSUP_H_
#define WINDOWSUP_H_

#include "mainheader.h"
#include "randombool.h"
extern pthread_mutex_t lock;
extern pthread_cond_t con;
extern pthread_condattr_t cattr;

void *Lockwins_PSG_BackL(void *arg);
void *Lockwins_PSG_BackR(void *arg);
void *Lockwins_PSG_Front(void *arg);
void *Lockwins_DRV(void *arg);
void *LockAll(void *data);

#endif /* WINDOWSUP_H_ */
