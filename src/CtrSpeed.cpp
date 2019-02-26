/*
 * CtrSpeed.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */
#include "windows.h"
#include "convar.h"
extern int rc;



//It receives moist_signal form the SenMoistDetector() or SenPlluFogDetector() related to the humidity or pollution and will turn the heal lamp On or Off
void *WindowsUp(void *data){
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"WindowsUp");
	eg->val = 1;
	pthread_exit(eg);


}

//Will detect the traffic light
void *Camera(void *data){
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Camera");
	eg->val = 1;
	pthread_exit(eg);


}

//Cameras will send signal from traffic light or obstacles to control the speed
void *Speedometer(void *speed_signal){
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Speedometer");
	eg->val = 1;
	pthread_exit(eg);


}
