/*
 * windowsup.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */
#include "windowsup.h"
int res;
//It receives moist_signal form the SenMoistDetector() or SenPlluFogDetector() related to the humidity or pollution and will turn the heal lamp On or Off

void *LockAll(void *data){
	int i;
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	struct return_value *resp;
	eg->core_No = CPU_COUNT(&cpuset);
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"LockAll");
	pthread_t lockwin[4];

	res = pthread_create(&lockwin[0], NULL, Lockwins_PSG_BackL, (void *)&my_data);
	res = pthread_create(&lockwin[1], NULL, Lockwins_PSG_BackR, (void *)&my_data);
	res = pthread_create(&lockwin[2], NULL, Lockwins_PSG_Front, (void *)&my_data);
	res = pthread_create(&lockwin[3], NULL, Lockwins_DRV, (void *)&my_data);

	for( i = 0; i < 4; i++ ) {
		res = pthread_join(lockwin[i], (void**)&resp);
		cout  << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;
		if (res) {
		   cout << "Error in LockAll:unable to join," << res << endl;
		   exit(-1);
		}
	};
	eg->val = 1;
	pthread_exit(eg);
};
void *Lockwins_PSG_BackL(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Lockwins_PSG_BackL");
	eg->val = 1;
	pthread_exit(eg);
};
void *Lockwins_PSG_BackR(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Lockwins_PSG_BackR");
	eg->val = 1;
	pthread_exit(eg);
};
void *Lockwins_PSG_Front(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Lockwins_PSG_Front");
	eg->val = 1;
	pthread_exit(eg);
};
void *Lockwins_DRV(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Lockwins_DRV");
	eg->val = 1;
	pthread_exit(eg);
};

