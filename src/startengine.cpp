/*
 * start_engine.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: mahsa
 */
#include "startengine.h"

int battery_capacity = 1;

int eng_status;
void *StartEngine(void *data){

	struct thread_data *my_data = (struct thread_data *) data;
	cout << "We are in the StartEngine Func" << endl;
	cout << my_data->message << endl;
	my_data->thread_id = pthread_self();

	//Check the battery
	pthread_mutex_lock(&lock);
	battery_capacity = 200;
	pthread_mutex_unlock(&lock);


	//check the seat belt

	/*if (1 and battery_level >1){
		eng_status = 1;
		cout << endl << "Engine has been started" << endl;
	}
	else {
		eng_status = 0;
		cout << "Warning " << endl;
	};
*/
	pthread_exit(&eng_status);
};

//Check the battery right after the car starts, and will send a alert to Warning() if the battery in Low.


void *CheckBattery(void *data){
	//int battery_level = 0;
	struct return_value *eg = new struct return_value;
	strcpy(eg->fun_name,"CheckBattery");
	struct thread_data *my_data = (struct thread_data *) data;
	int a = 0;
	//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << endl;
	my_data->message = "Checking the Battery";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	a = RandInt(5,200);
	cout << endl << "int BATTERY RAND " << a << endl;
	switch(a){
		case 5 ... 50:
			cout << "Battery is LOW" << endl;
			eg->val = 1;
			break;
		case 51 ... 100:
			cout << "Battery level is MEDIUM" << endl;
			eg->val = 2;
			break;
		case 101 ... 150:
			cout << "Battery level is HIGH" << endl;
			eg->val = 3;
			break;
		case 151 ... 200:
			cout << "Battery is FULL" << endl;
			eg->val = 4;
			break;
		};
	cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << "  " << eg->fun_name << " Thread_ID= " << thr_data.thread_id << "  eg-thr-id = " << eg->thr_id << endl;
	pthread_exit(eg);
};

//After starting the car, the seat belt must be fasten. If not send a alert to Warning()
void *CheckSeatBelt(void *data){
	struct return_value *eg = new struct return_value;
	strcpy(eg->fun_name,"CheckSeatBelt");
	struct thread_data *my_data = (struct thread_data *) data;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	my_data->message = "Checking the SeatBelt";
	//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << endl;
	eg->val = RandBool();
	cout << "bool RAND " << eg->val << endl;

	cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) <<  "  " <<  eg->fun_name << " Thread_ID= " << thr_data.thread_id << "  eg thr id = " << eg->thr_id << endl;
	pthread_exit(eg);

};

//Check the fuel tank right after the car starts, and will send a alert to Warning() if the fuel in Low.
void *FuelControll(void *data){

	pthread_t tid = pthread_self();
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	strcpy(eg->fun_name,"FuelControll");
	my_data->thread_id = tid;
	eg->thr_id = tid;
	int f = 0;
	my_data->message = "Checking the Fuel Tank";
	//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << endl;
	//my_data->thread_id = pthread_self();
	f = RandInt(10,150);
	cout << "int FUEL RAND " << f << endl;

	switch(f){
		case 10 ... 50:
			cout << "Fuel Tank is EMPTY" << endl;
			eg->val = 1;

			break;
		case 51 ... 100:
			cout << "Fuel Tank is HALF EMPTY" << endl;
			eg->val = 1;
			break;
		case 101 ... 150:
			cout << "Fuel Tank is FULL" << endl;
			eg->val = 1;
			break;

		};

	cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) << "  " << eg->fun_name << " Thread_ID= " << thr_data.thread_id << "  eg-thr-id = " << eg->thr_id << endl;
	pthread_exit(eg);
};




