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
extern pthread_mutex_t lock;
extern pthread_cond_t con;
extern pthread_condattr_t cattr;

void *HeadLampController(void *);
void *Camera(void *);
void *Speedometer(void *);

#endif /* CTRSPEED_H_ */
