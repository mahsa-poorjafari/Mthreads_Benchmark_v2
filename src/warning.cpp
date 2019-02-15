/*
 * warning.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: mahsa
 */

#include "mainheader.h"
#include "warning.h"
struct thread_data *alert_data;

// Warning light or Sound warning in case of any require alert.
void *Warning(void *alert_signal){
	alert_data = (struct thread_data *) alert_signal;
	cout << "-------------Warning-------------" << endl;
	int alarm = alert_data->type_val;
	alert_data->thread_id = pthread_self();
	switch(alarm){
		case 1 : cout << "Doors are open." << endl;
					break;
		case 2 : cout << "Light are on" << endl;
					break;
		case 3 : cout << "Speed is out of limit" << endl;
					break;
		default : cout << "Something is wrong" << endl;
					break;
	}

	pthread_exit(NULL);
	//return NULL;

}



