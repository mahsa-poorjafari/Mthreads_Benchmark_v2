/*
 * wipers.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: mahsa
 */
#include "wipers.h"
#include "windowscreen.h"

//It receives moist_signal form the SenMoistDetector() related to the humidity or wet windows and will turn the wipers On or Off
void *Wipers(void *data){
	int rc;
	//void *wiper_status;
	struct return_value *resp;
	struct thread_data *my_data = (struct thread_data *) data;
	my_data->message = "Turn the wipers on?";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	pthread_t winthr;
	rc = pthread_create(&winthr, NULL, WindowScreenClean, (void *)&thr_data);
	rc = pthread_join(winthr, (void**)&resp);
	if (resp->val){
		cout << "Wipers on " << endl;
	}
	cout << resp->fun_name << " Thread_ID= " << thr_data.thread_id << "  " <<  resp->thr_id << endl;
	strcpy(resp->fun_name,"Wipers");
	resp->thr_id = tid;

	pthread_exit(&resp);
};

