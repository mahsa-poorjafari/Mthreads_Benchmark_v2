/*
 * Windows.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */

#include "windows.h"
#include "convar.h"


int rc;

//lock all door
void *LockAll(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	strcpy(eg->fun_name,"LockAll");
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	eg->val=1;
	cout << "All doors has been locked" << endl;

	my_data->type_name = "which door" ;
	my_data->message = "Ask to clock all the doors";
	my_data->signal_name = "lock_all_doors";

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
	//cout << "In CheckDoors, child thread" << endl;
	//cout << "Thread ID : " << eg->thread_id << "  Thread closeD Prio: " << param.sched_priority << endl;
	//cout << " Message : " << door_data->message << endl;
	//to simulate the real life, just randomly set the value to be different.
	/* srand(time(NULL));
	float r = (float) rand()/RAND_MAX;
	randbool = (r < 0.5) ? true : false;
	cout << endl << "created Random number: " << r << endl;
	cout << endl << "randbool: " << randbool << endl;
	*/

	//cout << " Signal: " << door_data->signal_name << "= " << door_data->signal_val  << endl;

	//win_data.signal_name = "doors_status";
	//win_data.message = "Doors has been checked";
	done = 1;
	//pthread_cond_signal(&con);
	//pthread_mutex_unlock(&lock);
	//pthread_exit(&my_data->signal_val);

	d = (int) RandBool();
	my_data->signal_val= d;
	my_data->signal_name = "Has the door locked?";
	eg->val = d;
	pthread_exit(eg);

}

//This is the parent thread. door windows will be closed, if the doors are open either the car is turn off.
void *CtrWindows(void *data){
	struct return_value *resp;
	pthread_t ctrdoors[2];

	int *door_status;

	struct thread_data *win_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;

    //my_data= (struct thread_data *) data;
	int n=0;
    cout << "Which windows?" << endl;
	cout << "1(driver side powerwindow)" << endl<< "2(front passenger side powerwindow)" << endl << "3(back-left passenger side powerwindow) "<< endl<<"4(back-right passenger side powerwindow) "<<endl<<"5(All):"<< endl;
	cin >> n;

	pthread_t tid = pthread_self();
	win_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CtrWindows");
	//win_data->message = "Ask to control the windows";
	//win_data->signal_name = "check_windows";
	//win_data->signal_val = false;

	//win_data->type_name = "which windows";
    cout << "In CtrWindows, Parent Threads" << endl;
    //cout << "Thread ID : " << win_data->thread_id<< endl;
    //cout << " Message : " << win_data->message << endl;
	//cout << " Signal: " << win_data->signal_name << "= " << win_data->signal_val  << endl;
	//cout << " Type: " << win_data->type_name << "=> ";

	//rc =  pthread_setschedprio(ctrdoors,15);

	switch(n){
	case 1:
		cout << "driver side powerwindow" << endl;
		break;
	case 2:
		cout << "front passenger side powerwindow" << endl;
		rc = pthread_create(&ctrdoors[0], NULL, CheckDoors, (void *)&win_data);
		pthread_join(ctrdoors[0], (void **) &resp);
		break;
	case 3:
		cout << "back-left passenger side powerwindow" << endl;
		break;
	case 4:
		cout << "back-right passenger side powerwindow" << endl;
		break;
	case 5:
		cout << "All the Windows" << endl;
		rc = pthread_create(&ctrdoors[1], NULL, LockAll, (void *)&win_data);
		pthread_join(ctrdoors[1], (void **) &resp);
		break;
	default:
		cout << "Something is wrong" << endl;
		break;
	};

    if (rc) {
    	cout << "Error:unable to create thread," << rc << endl;
    	exit(-1);
    };
    //thr_join((void *)&door_data);
    //pthread_join(ctrdoors, (void **) &resp);

    //cout << "  door_status:  " << *door_status  << endl;
    eg->val = ( resp->val) ? true : false;
    /*
    if (pthread_join(ctrdoors, (void **) &door_status) != 0) {
      cout << "Creating ctrdoors Thread failed." << endl;
      exit(3);
    }
    else {
    	cout << "  door_status:  " << *door_status  << endl;
    	window_status = ( *door_status) ? true : false;
    };
    */

    cout << "Thread ID : " << win_data->thread_id << "  eg thr id = " << eg->thr_id  << endl;

	done = 1;

    pthread_exit(eg);

}

