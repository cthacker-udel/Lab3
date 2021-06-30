#ifndef TASK_HPP_
#define TASK_HPP_
#include <iostream>
#include <stdlib.h>
using namespace std;

class Task {
	friend class DNode;
	friend class DLL;
	int tasknum; //I gave each task a random number for easier manipulation
	string task; //task
	int priority; //task's priority (1, 2, or 3 for high, med, or low)
	int hr; //for total number of hours
	int min;  //for the number of total minutes
public:
	Task(string t, int p, int h, int m);
	Task();
	void printTask();
};



#endif /* TASK_HPP_ */
