/*
 * windowscreen.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: mahsa
 */

#include "windowscreen.h"
#include "moistsensor.h"

void *WindowScreenClean(void *data){
	int rc;
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *resp;
	my_data->message = "Checking the window screen";

	pthread_t tid = pthread_self();
	my_data->thread_id = tid;

	pthread_t tempthr;
	rc = pthread_create(&tempthr, NULL, SenMoistDetector, (void *)&thr_data);
	rc = pthread_join(tempthr, (void**)&resp);
	cout << resp->fun_name << " Thread_ID resp= " << resp->thr_id << " rep-val= " << resp->val << endl;
	//cout << endl << "win_status " << win_status << endl;
	if (resp->val){
		resp->val = 1;
	}else{
		resp->val = 0;
	}
	strcpy(resp->fun_name,"WindowScreenClean");
	resp->thr_id=tid;

	pthread_exit(&resp);

};

