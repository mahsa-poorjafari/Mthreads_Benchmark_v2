/*
 * CtrSpeed.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */

#include "CtrSpeed.h"

//Cameras will send signal from traffic light or obstacles to control the speed
void *Speedometer(void *data){
	int res;
	int current_speed = 0;
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	struct return_value *resp = new struct return_value;
	pthread_t ctrspeed;
	pthread_t tid = pthread_self();
	eg->core_No = CPU_COUNT(&cpuset);
	my_data->thread_id = tid;
	eg->thr_id = tid;

	strcpy(eg->fun_name,"Speedometer");
	eg->val = 13;
	current_speed = RandInt(5,20);
	cout << "current_speed  " << current_speed << endl;
	if (current_speed > 10){
		cout << "Slow DOWN" << endl;
		eg->val = 0;
		res = pthread_create(&ctrspeed, NULL, SlowDown, (void *)&thr_data);
	} else if(current_speed <= 10 or current_speed >= 5) {
		cout << "Ready to PARK" << endl;
		res = pthread_create(&ctrspeed, NULL, ReadToPark, (void *)&thr_data);
		eg->val = 1;
	}else if (current_speed < 5){
		cout << "Level Up the Speed" << endl;
		eg->val = 2;
		res = pthread_create(&ctrspeed, NULL, LevelUp, (void *)&thr_data);
	}else {
		cout << "Speed number out of range" << endl;
	};

	res = pthread_join(ctrspeed, (void**)&resp);

	if (res) {
		 cout << "Error (in Speedometer):unable to join," << res << endl;
		 exit(-1);
	}
	cout << "In Speedometer function=> Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

	pthread_exit(eg);


};
void *SlowDown(void *data){

	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;

	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	eg->val = 1;
	strcpy(eg->fun_name,"SlowDown");
	pthread_exit(eg);
};

void *ReadToPark(void *data){

	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;

	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	eg->val = 1;
	strcpy(eg->fun_name,"ReadToPark");
	pthread_exit(eg);
};

void *LevelUp(void *data){

	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;

	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	eg->val = 1;
	strcpy(eg->fun_name,"LevelUp");
	pthread_exit(eg);
};







