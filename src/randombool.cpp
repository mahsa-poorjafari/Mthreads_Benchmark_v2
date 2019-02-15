/*
 * random_bool.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: mahsa
 */
#include "randombool.h"

bool RandBool() {
	bool randbool;
	pthread_mutex_lock(&lock);
	srand(time(NULL));
	float r = (float) rand()/RAND_MAX;
	//cout << endl << "created Random Number: " << r << endl;
	randbool = (r < 0.5) ? true : false;
	pthread_mutex_unlock(&lock);
	//cout << endl << "randbool: " << randbool << endl;
	return(randbool);
}
