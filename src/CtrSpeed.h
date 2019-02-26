/*
 * CtrSpeed.h
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */

#ifndef CTRSPEED_H_
#define CTRSPEED_H_

#include "mainheader.h"
#include "randombool.h"
#include "randomint.h"
#include "windows.h"
#include "convar.h"
extern pthread_mutex_t lock;
extern pthread_cond_t con;
extern pthread_condattr_t cattr;

void *HeadLampController(void *);

void *Speedometer(void *);
void *SlowDown(void *);
void *LevelUp(void *);
void *ReadToPark(void *);

#endif /* CTRSPEED_H_ */
