/*
 * randomint.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: mahsa
 */

#include "randomint.h"


int RandInt(int min, int max){
	pthread_mutex_lock(&lock);
	int rint = 0;
	/* initialize random seed: */
	srand (time(NULL));
	//min + rand() % (( max + 1 ) - min);
	rint = min + rand() % (( max + 1 ) - min);
	pthread_mutex_unlock(&lock);
	return(rint);
};
