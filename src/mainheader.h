/*
 * mainheader.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */

#ifndef MAINHEADER_H_
#define MAINHEADER_H_

#include <iostream>
//#include <sys/resource.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "randomint.h"
#include "randombool.h"
using namespace std;

extern sched_param param;
extern int policy;
extern bool done;
struct thread_data {
	bool isActive;
	int thread_id;
	char const *message;
	char const *signal_name;
	bool signal_val;
	char const * type_name;
	int type_val;
};
struct return_value {
	char fun_name[32];
	int val;
	int thr_id;
};
extern struct thread_data thr_data;
extern pthread_mutex_t lock;
extern pthread_cond_t con;
extern cpu_set_t cpuset;

#endif /* MAINHEADER_H_ */