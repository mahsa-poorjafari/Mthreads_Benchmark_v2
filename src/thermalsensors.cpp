/*
 * thermalsensors.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: mahsa
 */
#include "thermalsensors.h"
#include "mainheader.h"
//Check the inside and outside temperature. The temperature value will create randomly and send to AirConditioner()
void *SenThermal(void *data){

	int t;

	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	my_data->message = "Temporal sensors ";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	strcpy(eg->fun_name,"SenThermal");
	eg->thr_id = tid;
	t = RandInt(-20,40);
	cout << "random temporal Int " << t << endl;
	eg->val = t;


	switch(t){
		case -20 ... -10:
			cout << "Weather is Freezing" << endl;
			eg->val = 4;
			break;
		case -9 ... -0:
			cout << "Weather is Cold" << endl;
			eg->val = 3;
			break;
		case 1 ... 10:
			cout << "Weather is good" << endl;
			eg->val = 2;
			break;
		case 11 ... 40:
			cout << "Weather is Hot" << endl;
			eg->val = 1;
			break;
	}
	cout << eg->fun_name << " Thread_ID= " << thr_data.thread_id  << "  eg-thr-id = " << eg->thr_id << endl;

	pthread_exit(eg);

};

