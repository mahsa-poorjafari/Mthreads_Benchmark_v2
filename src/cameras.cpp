/*
 * cameras.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: mahsa
 */

#include "cameras.h"
int policy = 0;
//Will detect the obstacle
void *Camera(void *data){
	int res;
	int i;
	struct thread_data *my_data = (struct thread_data *) data;
	struct return_value *eg = new struct return_value;
	struct return_value *resp;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->core_No = CPU_COUNT(&cpuset);
	eg->thr_id = tid;
	strcpy(eg->fun_name,"Camera");
	pthread_attr_t cattr;
	pthread_t cameras[5];
	res = pthread_attr_init(&cattr);
	pthread_attr_getschedpolicy(&cattr, &policy);
	param.sched_priority = 1;
	res = pthread_attr_setschedparam (&cattr, &param);
	res = pthread_create(&cameras[0], &cattr, CameraBackDown, (void *)&my_data);
	res = pthread_create(&cameras[1], &cattr, CameraBackUp, (void *)&my_data);
	param.sched_priority = 2;
	res = pthread_attr_setschedparam (&cattr, &param);
	res = pthread_create(&cameras[2], &cattr, CameraLeft, (void *)&my_data);
	res = pthread_create(&cameras[3], &cattr, CameraRight, (void *)&my_data);
	res = pthread_create(&cameras[4], &cattr, CameraFront, (void *)&my_data);

	for( i = 0; i < 5; i++ ) {
		res = pthread_join(cameras[i], (void**)&resp);
		if (res) {
			cout << "Error in Camera :unable to join," << res << endl;
			exit(-1);
		};
		cout << "Thread ID= " << resp->thr_id <<"  " << resp->fun_name << " Returned= " << resp->val << endl;

	};
	eg->val = 1;

	pthread_exit(eg);

}
void *CameraBackUp(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CameraBackUp");
	bool obstacle=false;
	obstacle = ChckObstacle();
	eg->val = (obstacle) ? 0 : 1;
	pthread_exit(eg);
};
void *CameraFront(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CameraFront");
	bool obstacle=false;
	obstacle = ChckObstacle();
	eg->val = (obstacle) ? 0 : 1;
	pthread_exit(eg);
};
void *CameraBackDown(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CameraBackDown");
	bool obstacle=false;
	obstacle = ChckObstacle();
	eg->val = (obstacle) ? 0 : 1;
	pthread_exit(eg);
};
void *CameraLeft(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CameraLeft");
	bool obstacle=false;
	obstacle = ChckObstacle();
	eg->val = (obstacle) ? 0 : 1;
	pthread_exit(eg);
};
void *CameraRight(void *arg){
	struct thread_data *my_data = (struct thread_data *) arg;
	struct return_value *eg = new struct return_value;
	pthread_t tid = pthread_self();
	my_data->thread_id = tid;
	eg->thr_id = tid;
	strcpy(eg->fun_name,"CameraRight");
	bool obstacle=false;
	obstacle = ChckObstacle();
	eg->val = (obstacle) ? 0 : 1;
	pthread_exit(eg);
};

bool ChckObstacle (){
	bool rt = false;
	int distance = 0;
	// distance- Meter
	distance = RandInt(0,5);
	if (distance<=1) {
		cout << "Stop OR you hit an Obstacle " << endl;
		rt = false;

	}else{
		cout << "You can go further" << endl;
		rt = true;
	};

	return rt;
}

