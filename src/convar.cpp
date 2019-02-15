/*
 * convar.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */
#include "mainheader.h"
#include "windows.h"
#include "convar.h"

void thr_join(void *arg){
	pthread_mutex_lock(&lock);
	while(done){
		pthread_cond_wait(&con, &lock);
	}
	pthread_mutex_unlock(&lock);

}



