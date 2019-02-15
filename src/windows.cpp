/*
 * Windows.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */
#include "mainheader.h"
#include "windows.h"
#include "convar.h"
#include "isActive.h"
#include "randombool.h"

int rc;
struct thread_data *my_data;
//lock all door
void *LockAll(void *arg){
	struct thread_data *lock_data = (struct thread_data *) arg;
	lock_data->isActive = true;
	cout << "All doors has been locked" << endl;
	lock_data->type_name = "which door" ;
	lock_data->message = "Ask to clock all the doors";
	lock_data->signal_name = "lock_all_doors";
	int result = 1;
	lock_data->isActive = false;
	pthread_exit(&result);
}

//This is a parent thread = If doors are open, lock the windows,
void *CheckDoors(void *arg){

	bool randbool = false;
	int d = 0;
	struct thread_data *door_data = (struct thread_data *) arg;

	//pthread_mutex_lock(&lock);
    door_data->thread_id = pthread_self();
    door_data->isActive = true;
    door_data->message = "Ask to check the doors";
    door_data->signal_name = "check_doors";
	cout << "In CheckDoors, child thread" << endl;
	cout << "Thread ID : " << door_data->thread_id << "  Thread closeD Prio: " << param.sched_priority << endl;
	cout << " Message : " << door_data->message << endl;
	//to simulate the real life, just randomly set the value to be different.
	/* srand(time(NULL));
	float r = (float) rand()/RAND_MAX;
	randbool = (r < 0.5) ? true : false;
	cout << endl << "created Random number: " << r << endl;
	cout << endl << "randbool: " << randbool << endl;
	*/
	door_data->signal_val= RandBool();
	door_data->signal_name = "Has the door locked?";
	cout << " Signal: " << door_data->signal_name << "= " << door_data->signal_val  << endl;

	//win_data.signal_name = "doors_status";
	//win_data.message = "Doors has been checked";
	done = 1;
	//pthread_cond_signal(&con);
	//pthread_mutex_unlock(&lock);
	//pthread_exit(&my_data->signal_val);
	door_data->isActive = false;
	d = (int) randbool;
	pthread_exit(&d);

}

//This is the parent thread. door windows will be closed, if the doors are open either the car is turn off.
void *CtrWindows(void *data){

	pthread_t ctrdoors;
	bool window_status;
	int *door_status;
	//struct thread_data *my_data, door_data;
	struct thread_data *win_data = (struct thread_data *) data;

    //my_data= (struct thread_data *) data;
	win_data->isActive = true;
    cout << "Which windows?" << endl;
	cout << "1(Left) / 2(Right) / 3(Front) / 4(Back) / 5(All):";
	cin >> win_data->type_val;
	win_data->thread_id = pthread_self();
	win_data->message = "Ask to control the windows";
	win_data->signal_name = "check_windows";
	win_data->signal_val = false;

	win_data->type_name = "which windows";
    cout << "In CtrWindows, Parent Threads" << endl;
    cout << "Thread ID : " << win_data->thread_id<< endl;
    cout << " Message : " << win_data->message << endl;
	cout << " Signal: " << win_data->signal_name << "= " << win_data->signal_val  << endl;
	cout << " Type: " << win_data->type_name << "=> ";

	rc =  pthread_setschedprio(ctrdoors,15);

	if (win_data->type_val == 5){

		cout << "All the Windows" << endl;
		rc = pthread_create(&ctrdoors, NULL, LockAll, (void *)&win_data);

	}
	else {
		switch(win_data->type_val){
		case 1 : cout << "Left Windows" << endl;
					break;
		case 2 : cout << "Right Windows" << endl;
					break;
		case 3 : cout << "Front Windows" << endl;
					break;
		case 4 : cout << "Back Windows" << endl;
					break;
		}
		cout << "Thread with ID " << win_data->thread_id << " is active? " << isActive() << endl;
	    rc = pthread_create(&ctrdoors, NULL, CheckDoors, (void *)&win_data);
	};

    if (rc) {
    	cout << "Error:unable to create thread," << rc << endl;
    	exit(-1);
    }
    //thr_join((void *)&door_data);
    pthread_join(ctrdoors, (void **) &door_status);
    cout << "  door_status:  " << *door_status  << endl;
    window_status = ( *door_status) ? true : false;
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
    win_data->signal_name= "windows_status";
    win_data->signal_val = window_status;
    win_data->thread_id = pthread_self();
    cout << "Thread ID : " << win_data->thread_id;
    cout << " Signal: " << win_data->signal_name << "= " << win_data->signal_val  << endl;
    cout << '\a';

	done = 1;
	thr_data.isActive=false;
    pthread_exit(&window_status);

}

