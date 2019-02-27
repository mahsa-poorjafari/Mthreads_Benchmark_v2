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
	int i;
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *resp;
	my_data->message = "Checking the window screen";

	pthread_t tid = pthread_self();
	my_data->thread_id = tid;

	pthread_t winscrthr[2];
	rc = pthread_create(&winscrthr[0], NULL, WinScrFront, (void *)&thr_data);
	rc = pthread_create(&winscrthr[1], NULL, WinScrBack, (void *)&thr_data);
	for( i = 0; i < 2; i++ ) {
		  rc = pthread_join(winscrthr[i], (void**)&resp);
		  if (rc) {
			 cout << "Error in 1st scenario:unable to join," << rc << endl;
			 exit(-1);
		  }
		  cout << "Which Core " << resp->core_No  <<  "  " << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

	};
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

void *WinScrFront(void *arg){
	int rc;
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	struct return_value *resp;
	pthread_t tempthr;

	my_data->message = "Checking the Front window screen ";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->core_No = CPU_COUNT(&cpuset);
	strcpy(eg->fun_name,"WinScrFront");
	rc = pthread_create(&tempthr, NULL, SenMoistDetector, (void *)&thr_data);
	rc = pthread_join(tempthr, (void**)&resp);
	cout << resp->fun_name << " Thread_ID resp= " << resp->thr_id << " rep-val= " << resp->val << endl;
	eg->val = resp->val;
	pthread_exit(&eg);

};


void *WinScrBack(void *arg){
	int rc;
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	struct return_value *resp;
	pthread_t tempthr;

	my_data->message = "Checking the Back window screen ";
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->core_No = CPU_COUNT(&cpuset);
	strcpy(eg->fun_name,"WinScrBack");
	rc = pthread_create(&tempthr, NULL, SenMoistDetector, (void *)&thr_data);
	rc = pthread_join(tempthr, (void**)&resp);
	cout << resp->fun_name << " Thread_ID resp= " << resp->thr_id << " rep-val= " << resp->val << endl;
	eg->val = resp->val;
	pthread_exit(&eg);

};

