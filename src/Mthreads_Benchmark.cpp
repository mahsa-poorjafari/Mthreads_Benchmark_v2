/*
 * mt.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: mahsa
 */
#include "mainheader.h"
#include "windows.h"
#include "warning.h"
#include "airconditioner.h"
#include "isActive.h"
#include "startengine.h"
#include "wipers.h"

#include <thread>
#include <unistd.h>
#include <errno.h>


void *SenSmokeDetector();
void *HeadLampController();
void *Camera();
void *Speedometer(void *);

bool done = 0;

sched_param param;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;
struct thread_data thr_data;
cpu_set_t cpuset;


void *PrintHello(void *threadarg) {
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

   cout << endl << "Thread ID : " << my_data->thread_id;
   cout << " Message : " << my_data->message << endl;
   cout << '\a';

   pthread_exit(NULL);
};


int main () {
	int i;
	int rc;
	int policy = 0;
	int num_cores=1;
	int num_threads = 1;
	int scen_No = 0;
	//void *status;
	struct return_value *resp;
	int n_core = sysconf(_SC_NPROCESSORS_ONLN);

	cout << "4 scenario has been defined." << endl;
	cout << "(1) Turn On the engine"<< endl;
	cout << "(2) Opening the windows."<< endl;
	cout << "(3) Park the car"<< endl;
	cout << "(4) Driving in the highway"<< endl;
	cout << "Please choose one of the 4 scenarios:"<< endl;
	cin >> scen_No;
	cout << "Number of Logical cores " << n_core << endl;
	cout << "Number of Physical cores " << thread::hardware_concurrency() << endl;
	cout << "Enter the Number of Cores (1-3):";
	cin >> num_cores;
	if (num_cores >= n_core or num_cores<1	) {
		cout<< "core number is out of range" << endl;
		exit(EXIT_FAILURE);
	};

	switch(scen_No){
	case 1:
		num_threads = 5;
		break;
	}
	pthread_attr_t tattr;
	pthread_t threads[num_threads];


	/* initialized with default attributes */
	rc = pthread_attr_init(&tattr);
	/*currently, only the Solaris SCHED_OTHER default value is supported in pthreads. Attempting to set policy as SCHED_FIFO or SCHED_RR will result in the error ENOSUP.  */
	/* Default scheduling policy is SCHED_OTHER */
	pthread_attr_getschedpolicy(&tattr, &policy);


	CPU_ZERO(&cpuset);
	switch(scen_No){
	case 1:

		cout << endl << "-----------main()-----------"<< endl << "Scenario(1): 5 thread for 5 function has been created." << endl;

		try {
			CPU_SET(1, &cpuset);
			//rc = pthread_setaffinity_np(threads[1], sizeof(cpuset), &cpuset);
			param.sched_priority = 1;
			rc = pthread_attr_setschedparam (&tattr, &param);
			rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
			rc = pthread_create(&threads[0], &tattr, FuelControll, (void *)&thr_data);
			rc = pthread_create(&threads[1], &tattr, CheckBattery, (void *)&thr_data);

			param.sched_priority = 2;
			rc = pthread_attr_setschedparam (&tattr, &param);
			if (num_cores>1) {
				//cout << "if num_cores>1 " << endl;
				CPU_SET(2, &cpuset);
				rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
			};

			rc = pthread_create(&threads[2], &tattr, CheckSeatBelt, (void *)&thr_data);
			rc = pthread_create(&threads[3], &tattr, Wipers, (void *)&thr_data);

			param.sched_priority = 3;
			rc = pthread_attr_setschedparam (&tattr, &param);
			if (num_cores>2) {
				//cout << "if num_cores>2 " << endl;
				CPU_SET(3, &cpuset);
				rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
			};

			rc = pthread_create(&threads[4], &tattr, AirConditioner, (void *)&thr_data);

		}catch (const char* msg) {
		     cerr << msg << endl;
		   }
		//if (rc != 0) {	cout << "pthread_setaffinity_np ERROR"; };
		/*
		for( i = 0; i < num_cores; i++ ) {
			  cout << endl << "main() : creating thread, " << i << endl;
			  rc = pthread_setschedprio(threads[i],i+1);RAND
			  param.sched_priority = i+1;
			  rc = pthread_setschedparam(threads[i], policy, &param);
			  cout << "param.sched_priority for Thread " << i << ": " << param.sched_priority << endl;
			  rc = pthread_create(&threads[i], &tattr, StartEngine, (void *)&thr_data);

			  if (rc) {
				 cout << "Error:unable to create thread for StartEngine" << rc << endl;
				 exit(-1);
			  }
		   }
		*/
		pthread_attr_destroy(&tattr);
		for( i = 0; i < 5; i++ ) {
			  rc = pthread_join(threads[i], (void**)&resp);
			  if (rc) {
				 cout << "Error:unable to join," << rc << endl;
				 exit(-1);
			  }
			  cout << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

		   }
		free(resp);
		break;
	case 2:
		thr_data.message="Opening the windows.";
		for( i = 0; i < num_cores; i++ ) {
			  cout << endl << "main() : creating thread, " << i << endl;
			  rc = pthread_setschedprio(threads[i],i+1);
			  param.sched_priority = i+1;
			  rc = pthread_setschedparam(threads[i], policy, &param);
			  cout << "param.sched_priority for Thread " << i << ": " << param.sched_priority << endl;
			  rc = pthread_create(&threads[i], &tattr, CtrWindows, (void *)&thr_data);

			  if (rc) {
				 cout << "Error:unable to create thread for CtrWindows" << rc << endl;
				 exit(-1);
			  }
		   }
		break;
	default:
		thr_data.message="PrintHello.";
		for( i = 0; i < num_cores; i++ ) {
			rc = pthread_create(&threads[i], &tattr, PrintHello, (void *)&thr_data);
		}
	};



	//rc = pthread_create(&thr[0], NULL, CtrWindows, (void *)&thr_data);

	//cout <<"main()-----------------------" << endl << " control the windows" << endl;

	//rc = pthread_create(&thr[0], NULL, CtrWindows, (void *)&thr_data);
	/*
	cout << "Thread with ID " << thr_data.thread_id << " is active? " << isActive() << endl;
	if (rc) {
	   cout << "Error:unable to create thread," << rc << endl;
	   exit(-1);
	}
	pthread_join(thr[0], &window_status);
	cout <<"main() : checking the windows finished " <<endl << "---------------------" << endl;
	//ret = pthread_create(&tid, &tattr, PrintHello, (void *)&prio_data);

	ret =  pthread_setschedprio(thrwar,1);
	td_data.type_name = "Alert type";
	td_data.type_val = 3;
	ret = pthread_create(&thrwar, NULL, Warning, (void *)&td_data);
	if (ret) {
	   cout << "Error:unable to create thread for Warning " << ret << endl;
	   exit(-1);
	}

	//pthread_join(tid, &window_status);
	pthread_join(thrwar, &window_status);
	*/
	pthread_exit(NULL);

}





//will send a alert to Warning() if any smoke will detect.
void *SenSmokeDetector(){
	return NULL;

}










//It receives moist_signal form the SenMoistDetector() or SenPlluFogDetector() related to the humidity or pollution and will turn the heal lamp On or Off
void *HeadLampController(void *moist_plo_signal){
	return NULL;

}

//Will detect the traffic light
void *Camera(){
	return NULL;

}

//Cameras will send signal from traffic light or obstacles to control the speed
void *Speedometer(void *speed_signal){
	return NULL;

}




