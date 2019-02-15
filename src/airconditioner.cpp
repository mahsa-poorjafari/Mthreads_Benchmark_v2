/*
 * airconditioner.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: mahsa
 */

#include "mainheader.h"
#include "airconditioner.h"
#include "thermalsensors.h"


//The heater or cooler will be controlled by this function
void *AirConditioner(void *data){
	int rc = 1;
	//void *air_status;
	struct return_value *resp;
	struct return_value *air = new struct return_value;
	strcpy(air->fun_name,"AirConditioner");

	struct thread_data *my_data = (struct thread_data *) data;
	my_data->message = "Turn the AirConditioner on?";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	air->thr_id=tid;
	pthread_t winthr;
	rc = pthread_create(&winthr, NULL, SenThermal, (void *)&thr_data);
	rc = pthread_join(winthr, (void**)&resp);
	cout << resp->fun_name << "  " << resp->val << endl;
	// No 1 is code for Turn on the heater
	// No 2 is code for Turn on the cooler
	// No 0 is code for do nothing
	// No -1 is code for something is wrong
	switch(resp->val){
		case 1:

			cout << endl << "Turn on the cooler " << endl;
			air->val=2;
			break;
		case 2:
			cout << endl << "Do nothing (No heater or cooler) " << endl;
			air->val=0;
			break;
		case 3:
		case 4:
			cout << endl << "Turn on the heater " << endl;
			air->val=1;
			break;
		default:
			cout << endl << "Something is wrong" << endl;
			air->val=-1;
	}

	cout << air->fun_name << " Thread_ID= " << thr_data.thread_id << " air->thr_id " << air->thr_id<< endl;
	//cout << endl << "win_status " << &air_status << endl;


	pthread_exit(air);


}
