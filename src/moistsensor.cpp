/*
 * moistsensor.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: mahsa
 */

#include "moistsensor.h"
#include "randombool.h"

//measures the humidity of outside, and send a signal to Wipers() or AirConditioner() or HeadLampController().
void *SenMoistDetector(void *data){
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	strcpy(eg->fun_name,"SenMoistDetector");

	bool a = 0;
	my_data->message = "Check the cleanness of the Windows";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id=tid;
	//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << endl;
	a = RandBool();
	if (a) {
		cout << "Windows are clean" <<endl;
		eg->val=0;
	}
	else{
		cout << "Windows are wet" << endl;
		eg->val=1;

	}
	//cout << endl << "bool RAND " << a << endl;
	cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << endl << eg->fun_name << " Thread_ID= " << thr_data.thread_id << " eg-thr-id " <<  eg->thr_id<< endl;
	pthread_exit(eg);

};
