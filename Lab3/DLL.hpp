#ifndef DLL_HPP_
#define DLL_HPP_

#include "DNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

class DLL {
	DNode *first;
	DNode *last;
	int numTasks;
	int tothrs;
	int totmin;
public:
	DLL();  // constructor - initializes an empty list

	DLL(string t, int p, int m, int s);  // constructor, initializes a list with one new node with data x

	void push(string t, int p, int h, int m);
		//does what you'd think, with a caveat that if the
		//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
		//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
		//task with a priority of 1, and insert the new task between the last task with a priority of
		//1 and the first task with a priority of 2
		//it also updates the total time of the list

	Task *pop();  //does what you'd think - make sure to update the total time of the list

	int remove(int tn); //removes a task (based on its number) and updates the total time of the list

	void moveUp(int tn);
		//moves task with number tn up one in the list.
		//If it is at the beginning of the list, it will be moved to the end of the list.
		//NOTE: if this moves a task up before a task with a higher priority (1 is
		//higher priority than 2 - I know the wording is a bit weird), then this
		//changes the priority of the task being moved to that higher priority

	void moveDown(int tn);
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to the beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being moved.

	void changePriority(int tn, int newp); //changes the priority of the task tn

	void listDuration(int *th, int *tm, int p);
		//gets the total list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)

	void printList();
		//prints out the entire list, along with the total time necessary to complete
		//all tasks on the list

	void printList(int p); //print out all tasks with a priority of p;

	~DLL();

	void addTime(int h, int m); //Helper function to add time to total time of list

	void removeTime(int h, int m); //Helper function to remove time from the total list of time
};


#endif /* DLL_HPP_ */
