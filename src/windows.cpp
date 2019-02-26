/*
 * Windows.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */

#include "windows.h"
#include "convar.h"
extern int rc;
//Open all the Windows
void *OpenAll(void *arg){

	int i;
	int policy = 0;
	struct return_value *resp;
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_attr_t oattr;
	pthread_t opwin[4];
	rc = pthread_attr_init(&oattr);
	pthread_attr_getschedpolicy(&oattr, &policy);
	param.sched_priority = 2;
	rc = pthread_attr_setschedparam (&oattr, &param);

	/*if (my_data->core_no>1){
		CPU_SET(2, &cpuset);
		my_data->core_no--;
		rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
	}*/

	strcpy(eg->fun_name,"OpenAll");
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	my_data->type_name = "which door" ;
	my_data->message = "Ask to clock all the doors";
	my_data->signal_name = "lock_all_doors";
	eg->val = 13;
	cout << " 4 thread will create for 4 windows. Thread ID " << eg->thr_id << endl;
	rc = pthread_create(&opwin[0], &oattr, powerwindow_DRV, (void *)&my_data);
	rc = pthread_create(&opwin[1], &oattr, powerwindow_PSG_BackL, (void *)&my_data);
	rc = pthread_create(&opwin[2], &oattr, powerwindow_PSG_BackR, (void *)&my_data);
	rc = pthread_create(&opwin[3], &oattr, powerwindow_PSG_Front, (void *)&my_data);

	for( i = 0; i < 4; i++ ) {
	    rc = pthread_join(opwin[i], (void**)&resp);
	    cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) <<  "  " << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;
	    if (rc) {
		   cout << "Error:unable to join," << rc << endl;
		   exit(-1);
	    }
	};

	pthread_mutex_lock( &condition_mutex );
	if (resp->val){
		cout << "-------hey--------" << endl;
		eg->val = 1;
		pthread_cond_signal( &con );
	};
	pthread_mutex_unlock( &condition_mutex );

	pthread_exit(eg);
}

//This is a parent thread = If doors are open, lock the windows,
void *CheckDoors(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	int d = 0;
	struct return_value *eg = new struct return_value;

	//pthread_mutex_lock(&lock);
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CheckDoors");

	my_data->message = "Ask to check the doors";
	my_data->signal_name = "check_doors";
	done = 1;

	d = (int) RandBool();
	my_data->signal_val= d;
	my_data->signal_name = "Has the door locked?";
	eg->val = d;
	pthread_exit(eg);

}

//This is the parent thread. door windows will be closed, if the doors are open either the car is turn off.
void *CtrWindows(void *data){
	rc = pthread_condattr_destroy(&cattr);
	rc = pthread_cond_init(&con, &cattr);
	struct return_value *resp;
	pthread_attr_t tattr;
	pthread_t ctrdoors;
	struct thread_data *win_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	cout << "thr_data.core_no= " << win_data->core_no << endl;
	//CPU_SET(2, &cpuset);
	//win_data->core_no--;
	rc = pthread_attr_init(&tattr);
	param.sched_priority = 1;
	rc = pthread_attr_setschedparam (&tattr, &param);
	//rc = pthread_attr_setaffinity_np(&tattr, sizeof(cpuset), &cpuset);
	int n=0;
	//int z;
	//int array[4] = {0,0,0,0};
    cout << "Which windows to be open?" << endl;
	cout << "1(driver side powerwindow)" << endl<< "2(front passenger side powerwindow)" << endl << "3(back-left passenger side powerwindow) "<< endl<<"4(back-right passenger side powerwindow) "<<endl<<"5(Open All):"<< endl;
	//cout << "e.g. 1 OR 1,2 etc";
	cin >> n;

	pthread_t tid = pthread_self();
	win_data->thread_id = tid;
	eg->thr_id = tid;

	strcpy(eg->fun_name,"CtrWindows");

    cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) <<  "  " << "In CtrWindows, Parent Threads ID " << eg->thr_id << endl;
    //pthread_mutex_lock(&lock);
	switch(n){
	case 1:
		cout << "driver side powerwindow" << endl;
		rc = pthread_create(&ctrdoors, &tattr, powerwindow_DRV, (void *)&win_data);

		break;
	case 2:
		cout << "front passenger side powerwindow" << endl;
		rc = pthread_create(&ctrdoors, &tattr, powerwindow_PSG_Front, (void *)&win_data);

		break;
	case 3:
		cout << "back-left passenger side powerwindow" << endl;
		rc = pthread_create(&ctrdoors, &tattr, powerwindow_PSG_BackL, (void *)&win_data);

		break;
	case 4:
		cout << "back-right passenger side powerwindow" << endl;
		rc = pthread_create(&ctrdoors, &tattr, powerwindow_PSG_BackR, (void *)&win_data);

		break;
	case 5:
	default:
		cout << "Open All the Windows" << endl;
		rc = pthread_create(&ctrdoors, &tattr, OpenAll, (void *)&win_data);

		break;
	};
	rc=pthread_join(ctrdoors, (void **) &resp);
    if (rc) {
	   cout << "Error:unable to join," << rc << endl;
	   exit(-1);
    }
	eg->val =  resp->val;
	pthread_mutex_lock( &condition_mutex );
	while(!resp->val){
		pthread_cond_wait(&con, &lock);
		//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) <<  "  " << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;
		//cout << "CPU_COUNT() " << CPU_COUNT(&cpuset) <<  "  " << "Thread ID : " << resp->thr_id << "  eg thr id = " << eg->thr_id  << endl;
	}
	pthread_mutex_unlock( &condition_mutex );

    pthread_exit(eg);

}

void *powerwindow_DRV(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"powerwindow_DRV");
	eg->val = 1;
    pthread_exit(eg);

};
void *powerwindow_PSG_BackL(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"powerwindow_PSG_BackL");
	eg->val = 2;
    pthread_exit(eg);

};
void *powerwindow_PSG_BackR(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"powerwindow_PSG_BackR");
	eg->val = 3;
    pthread_exit(eg);

};
void *powerwindow_PSG_Front(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"powerwindow_PSG_Front");
	eg->val = 4;
    pthread_exit(eg);

};

