/*
 * mt.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: mahsa
 */
#include "mainheader.h"

void *SenSmokeDetector();

bool done = 0;
struct timespec tp = {0, 10};

sched_param param;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;
pthread_condattr_t cattr;
struct thread_data thr_data;
cpu_set_t cpuset;


void *PrintHello(void *threadarg) {
   struct thread_data *my_data;
   struct return_value *eg = new struct return_value;
   my_data = (struct thread_data *) threadarg;
   pthread_t tid = pthread_self();
   my_data->thread_id = tid;
   eg->thr_id = tid;
   cout << endl << "Thread ID : " << my_data->thread_id;
   cout << " Message : " << my_data->message << endl;
   strcpy(eg->fun_name,"PrintHello");
   eg->val = 1;
   pthread_exit(eg);
};


int main () {
	int i;
	int while_counter = 0;
	int time_increment = 0;

	int rc;
	int policy = 0;
	int num_cores=1;
	int num_threads = 1;
	int scen_No = 0;

	struct return_value *resp = new struct return_value;
	strcpy(resp->fun_name,"Main");
	pthread_t tid = pthread_self();
	resp->thr_id = tid;
	int n_core = sysconf(_SC_NPROCESSORS_ONLN);
	tp.tv_nsec = 400;

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
	thr_data.core_no = num_cores;
	if (num_cores >= n_core or num_cores<1	) {
		cout<< "core number is out of range" << endl;
		exit(EXIT_FAILURE);
	};

	switch(scen_No){
	case 1:
		num_threads = 5;
		break;
	case 2:
		num_threads = 3;
		break;
	default:
		num_threads = 3;
		break;
	}
	pthread_attr_t tattr;
	pthread_t threads[num_threads];


	/* initialized with default attributes */
	rc = pthread_attr_init(&tattr);
	/*currently, only the Solaris SCHED_OTHER default value is supported in pthreads. Attempting to set policy as SCHED_FIFO or SCHED_RR will result in the error ENOSUP.  */
	/* Default scheduling policy is SCHED_OTHER */
	pthread_attr_getschedpolicy(&tattr, &policy);
	/* initialize an attribute to default value */
	rc = pthread_condattr_init(&cattr);


	CPU_ZERO(&cpuset);
	time_increment = 100;
	switch(scen_No){
	case 1:

		cout << endl << "-----------main()-----------"<< endl << "Scenario(1): 5 thread for 5 function has been created." << endl;
		while(true){
			while_counter+=1;
			try {

				CPU_SET(1, &cpuset);
				thr_data.core_no-- ;
				param.sched_priority = 1;
				rc = pthread_attr_setschedparam (&tattr, &param);
				rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				rc = pthread_create(&threads[0], &tattr, FuelControll, (void *)&thr_data);
				rc = pthread_create(&threads[1], &tattr, CheckBattery, (void *)&thr_data);

				param.sched_priority = 2;
				rc = pthread_attr_setschedparam (&tattr, &param);
				if (num_cores>1) {

					CPU_SET(2, &cpuset);
					thr_data.core_no--;
					rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				};

				rc = pthread_create(&threads[2], &tattr, CheckSeatBelt, (void *)&thr_data);
				rc = pthread_create(&threads[3], &tattr, Wipers, (void *)&thr_data);

				param.sched_priority = 3;
				rc = pthread_attr_setschedparam (&tattr, &param);
				if (num_cores>2) {

					CPU_SET(3, &cpuset);
					thr_data.core_no--;
					rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				};

				rc = pthread_create(&threads[4], &tattr, AirConditioner, (void *)&thr_data);

			}catch (const char* msg) {
				 cerr << msg << endl;
			};

			/* destroy an attribute */
			rc = pthread_condattr_destroy(&cattr);
			rc= pthread_attr_destroy(&tattr);

			for( i = 0; i < 5; i++ ) {
				  rc = pthread_join(threads[i], (void**)&resp);
				  if (rc) {
					 cout << "Error:unable to join," << rc << endl;
					 exit(-1);
				  }
				  cout << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

			   }
			//free(resp);
			//if(resp) { free(resp); };
			//sleep(1);
			nanosleep(&tp, NULL);
			tp.tv_nsec += time_increment;
			cout << "THE ENGINE STARTED..." << tp.tv_nsec << endl;
			cout << "===================End of "<< while_counter <<" While Loop========================" << endl;
		}//End of while

		break;

	case 2:
		cout << endl << "-----------main()-----------"<< endl << "Scenario(2): 3 thread for 3 function has been created." << endl;
		while(true){
			while_counter+=1;
			thr_data.message="Opening the windows.";
			try {
				tp.tv_nsec = 500;
				if (num_cores>1) {
					CPU_SET(2, &cpuset);
					thr_data.core_no--;
					rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				};

				param.sched_priority = 1;
				rc = pthread_attr_setschedparam (&tattr, &param);
				rc = pthread_create(&threads[0], &tattr, CtrWindows, (void *)&thr_data);
				if (rc) {
					cout << "Error:unable to create thread for CtrWindows" << rc << endl;
					exit(-1);
				}
				rc = pthread_condattr_destroy(&cattr);
				rc= pthread_attr_destroy(&tattr);
				rc = pthread_join(threads[0], (void**)&resp);
				cout << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;
				//TO DO with more core
			}catch(const char* msg) {
				 cerr << msg << endl;
			};

			//sleep(1);
			//if(resp) { free(resp); };
			nanosleep(&tp, NULL);
			tp.tv_nsec += time_increment;
			cout << "THE powerwindow DONE..." << endl;
			cout << "=================== End of "<< while_counter <<" While Loop========================" << endl;
			//cout << "thr_data.core_no left=" << thr_data.core_no << endl;
		}//end while
		break;

	case 3:
		cout << endl << "-----------main()-----------"<< endl << "Scenario(3): 14 thread for 14 function has been created." << endl;
		while(true){
			while_counter+=1;
			thr_data.message="Park the car.";
			try {
				tp.tv_nsec = 300;
				CPU_SET(1, &cpuset);
				thr_data.core_no-- ;
				param.sched_priority = 1;
				rc = pthread_attr_setschedparam (&tattr, &param);
				rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				rc = pthread_create(&threads[0], &tattr, Speedometer, (void *)&thr_data);
				rc = pthread_create(&threads[1], &tattr, CheckBattery, (void *)&thr_data);

				param.sched_priority = 2;
				rc = pthread_attr_setschedparam (&tattr, &param);
				if (num_cores>1) {

					CPU_SET(2, &cpuset);
					thr_data.core_no--;
					rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
				};


			}catch(const char* msg) {
				 cerr << msg << endl;
			};
			nanosleep(&tp, NULL);
			tp.tv_nsec += time_increment;
			cout << "PARK the car is DONE..." << endl;
			cout << "=================== End of "<< while_counter <<" While Loop========================" << endl;
			}
		break;


	default:
		thr_data.message="PrintHello.";
		for( i = 0; i < num_threads; i++ ) {
			rc = pthread_create(&threads[i], &tattr, PrintHello, (void *)&thr_data);
		};
		for( i = 0; i < num_threads; i++ ) {
			rc = pthread_join(threads[i], (void**)&resp);
			if (rc) {
				cout << "Error:unable to join," << rc << endl;
				exit(-1);
			};
			cout << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

		};
		nanosleep(&tp, NULL);
		//if(resp) { free(resp); };

	};

	pthread_exit(NULL);

}



//will send a alert to Warning() if any smoke will detect.
void *SenSmokeDetector(){
	return NULL;

}





