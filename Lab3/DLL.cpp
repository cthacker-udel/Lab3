#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}

	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/
	void DLL::push(string n, int p, int h, int m) {
		//does what you'd think, with a caveat that if the
		//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
		//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
		//task with a priority of 1, and insert the new task between the last task with a priority of
		//1 and the first task with a priority of 2
		//it also updates the total time of the list
		DNode *newNode = new DNode(n,p,h,m);
		totmin += newNode->task->min;
		tothrs += newNode->task->hr;
		numTasks++;
		if(first == NULL && last == NULL){
			first = newNode;
			last = newNode;
			return;
		}
		DNode *tempLast = last;
		while(tempLast != NULL && tempLast->task->priority > newNode->task->priority){
			tempLast = tempLast->prev;
		}
		if(tempLast == NULL){ // reached beginning of list
			newNode->next = first;
			newNode->prev = NULL;
			first->prev = newNode;
			first = newNode;
		}
		else if(tempLast == first && tempLast == last){
			tempLast->next = newNode;
			newNode->prev = tempLast;
			newNode->next = NULL;
			last = newNode;
		}
		else if(tempLast == first){
			tempLast->next->prev = newNode;
			newNode->next = tempLast->next;
			newNode->prev = tempLast;
			tempLast->next = newNode;
		}
		else if(tempLast == last){

			tempLast->next = newNode;
			newNode->prev = tempLast;
			newNode->next = NULL;
			last = newNode;

		}
		else{
			cout << "Landed in else statement" << endl;
			newNode->prev = tempLast;
			newNode->next = tempLast->next;
			tempLast->next->prev = newNode;
			tempLast->next = newNode;
		}

	}

	Task *DLL::pop() {
		//does what you'd think - make sure to update the total time of the list.
		//Note -this isn�t all that necessary for this particular project, but I
		//kinda had to make you write pop because it�s //fundamental to so much of
		//linked list data type uses (e.g., stack, undo).
		DNode *lastNode = last;
		Task *lastNodeTask = lastNode->task;
		tothrs -= lastNode->task->hr;
		totmin -= lastNode->task->min;
		numTasks--;
		if(lastNode->prev == NULL){
			delete lastNode;
			delete first;
			delete last;
			return lastNodeTask;
		}
		else{
			DNode *prevNode = lastNode->prev;
			lastNode->prev = NULL;
			prevNode->next = NULL;
			delete lastNode;
			return lastNodeTask;
		}
		return lastNodeTask;
	}

	void DLL::printList() {
		//prints out the entire list, along with the total time necessary to complete
		//all tasks on the list
		DNode *firstNode = first;
		while(firstNode != NULL){
			firstNode->task->printTask();
			firstNode = firstNode->next;
		}
	}

	void DLL::printList(int p) {
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
		DNode *firstNode = first;
		while(firstNode != NULL){
			if(firstNode->task->priority == p){
				firstNode->task->printTask();
			}
			firstNode = firstNode->next;
		}
	}

	void DLL::moveUp(int tn) {
		//moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		//NOTE: if this moves a task up before a task with a higher priority (1 is
		//higher priority than 2 - I know the wording is a bit weird), then this
		//changes the priority of the task being moved to that higher priority
		DNode *currNode = first;
		while(currNode != NULL){
			if(currNode->task->tasknum == tn){

				if(currNode->prev == NULL){ // currNode is head of list
					currNode->prev = last;
					last->next = currNode;
					first = currNode->next;
					first->prev = NULL;
					currNode->next = NULL;
					last = currNode;
					if(last->prev->task->priority < last->task->priority){
						last->task->priority = last->prev->task->priority;
					}
					break;
				}
				else if(currNode->next == NULL){ // currNode is tail of list
					currNode->prev->next = NULL;
					currNode->next = currNode->prev;
					currNode->prev = currNode->prev->prev;
					last->prev = currNode;
					last = currNode->next;
					if(last->task->priority < currNode->task->priority){
						currNode->task->priority = last->task->priority;
					}
				}
				else{
					DNode *prevPrev = currNode->prev->prev; // = NULL
					currNode->prev->next = currNode->next;
					currNode->prev->prev = currNode;
					currNode->next = currNode->prev;
					currNode->prev = prevPrev;
					if(prevPrev != NULL){
						prevPrev->next = currNode;
					}
					if(currNode->next->task->priority < currNode->task->priority){
						currNode->task->priority = currNode->next->task->priority;
					}
					if(currNode->next == first){
						first = currNode;
					}
				}

			}
			currNode = currNode->next;
		}

	}

	void DLL::listDuration(int *th, int *tm,int tp) {
		//gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		//I had you pass in the parameters as pointers for practice.
		int totMin = 0;
		int totHr = 0;
		DNode *firstNode = first;
		while(firstNode != NULL){
			if(firstNode->task->priority == tp){
				totMin += firstNode->task->min;
				totHr += firstNode->task->hr;
			}
			firstNode = firstNode->next;
		}
		*th = totHr;
		*tm = totMin;
		while(*tm >= 60){
			*th += 1;
			*tm -= 60;
		}
	}


	void DLL::moveDown(int tn) {
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to the beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being moved.
		DNode *currNode = first;
		while(currNode != NULL){
			if(currNode->task->tasknum == tn){ // node with tasknum is tail
				if(currNode->next == NULL){
					currNode->prev->next = NULL;
					currNode->prev = NULL;
					currNode->next = first;
					first->prev = currNode;
					first = currNode;
					break;
				}
				else if(currNode->prev == NULL){ // node with tasknum is head
					first = currNode->next;
					currNode->prev = currNode->next;
					currNode->next->prev = NULL;
					currNode->next = currNode->next->next;
					currNode->prev->next = currNode;
					if(first->task->priority > currNode->task->priority){
						currNode->task->priority = first->task->priority;
					}
					break;
				}
				else{
					// double check pointer reassignments
					if(currNode->next->task->priority > currNode->task->priority){
						currNode->task->priority = currNode->next->task->priority;
					}
					DNode *forwardNode = currNode->next->next;
					currNode->prev->next = currNode->next;
					currNode->next->prev = currNode->prev;
					currNode->next->next = currNode;
					currNode->prev = currNode->next;
					currNode->next = forwardNode;
					if(forwardNode != NULL){
						forwardNode->prev = currNode;
					}
					break;
				}
			}
			currNode = currNode->next;
		}
	}

	int DLL::remove(int tn) {
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The
		//biggest catch with this method is making sure you test to make sure the node
		//after and/or the node before the node you�re deleting aren�t NULL (i.e., you�re
		//not deleting the first or last node in the list)
		DNode *firstNode = first;
		if(firstNode->prev == NULL && firstNode->next == NULL && firstNode->task->tasknum == tn){ // last node
			delete firstNode;
			first = NULL;
			last = NULL;
			tothrs = 0;
			totmin = 0;
			numTasks--;
			return 1;
		}
		else if(firstNode->prev == NULL && firstNode->task->tasknum == tn){ // node is head
			// is first node
			DNode *frontNode = firstNode->next;
			removeTime(firstNode->task->hr,firstNode->task->min);
			frontNode->prev = NULL;
			firstNode->next = NULL;
			delete firstNode;
			first = frontNode;
			return 1;
		}
		else if(last->task->tasknum == tn){ // node is tail
			removeTime(last->task->hr,last->task->min);
			DNode *prevNode = last->prev;
			prevNode->next = NULL;
			last->prev = NULL;
			delete last;
			last = prevNode;
			return 1;
		}
		else{
			while(firstNode != NULL){
				if(firstNode->task->tasknum == tn){
					DNode *prevNode = firstNode->prev;
					prevNode->next = firstNode->next;
					firstNode->next->prev = prevNode;
					firstNode->prev = NULL;
					firstNode->next = NULL;
					removeTime(firstNode->task->hr,firstNode->task->min);
					delete firstNode;
					return 1;
				}
				firstNode = firstNode->next;
			}
			return 0;
		}
	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end
		//of the set of tasks with
		//that priority. In other words, if you have the following:
		/*  task1, 1, 2:20
			task2, 1, 3:20
			task3, 1, 1:15
			task4, 2, 3:10
			task5, 2, 1:10
			task6, 3, 3:15
			task7, 3, 2:54

		And you change task6's priority to 1, the resulting list should be:
			task1, 1, 2:20
			task2, 1, 3:20
			task3, 1, 1:15
			task6, 1, 3:15
			task4, 2, 3:10
			task5, 2, 1:10
			task7, 3, 2:54
		*/

		if(first == NULL || last == NULL){
			cout << "Cannot change priority of node if list is empty";
			return;
		}
		if(first == last){ // 1 node left
			first->task->priority = newp;
		}

		DNode *tempHead = first;

		/*
		 *
		 * removing node
		 *
		 */

		cout << "entering first while" << endl;
		while(tempHead != NULL){
			if(tempHead->task->tasknum == tn){
				if(tempHead->next == NULL){ // node is tail

					tempHead->prev->next = NULL;
					tempHead->prev = NULL;

					// node is removed

					break;

				}
				else if(tempHead->prev == NULL){ // node is head

					tempHead->next->prev = NULL;
					tempHead->next = NULL;

					// node is removed

					break;

				}
				else{

					tempHead->prev->next = tempHead->next;
					tempHead->next->prev = tempHead->prev;
					tempHead->prev = NULL;
					tempHead->next = NULL;

					// node is removed

					break;
				}

			}
			tempHead = tempHead->next;
		}

		/*
		 *
		 * node removed
		 *
		 */

		/*
		 *
		 * begin placement
		 *
		 *
		 */

		cout << "Entering second while" << endl;
		DNode *prevNode = last;
		while(prevNode != NULL){

			if(prevNode->task->priority == newp){

				prevNode->next->prev = tempHead;
				tempHead->prev = prevNode;
				tempHead->next = prevNode->next;
				prevNode->next = tempHead;
				tempHead->task->priority = newp;
				return;

			}
			prevNode = prevNode->prev;

		}
		// if we don't find the priority to place, then the priority doesnt exist, this loop below tests if we are trying to place newp = 3 and we only have 1 and 2 priorities
		cout << "Entering third while" << endl;
		prevNode = last;
		while(prevNode != NULL){

			if(prevNode->task->priority < newp){

				if(prevNode != last){

					tempHead->next = prevNode->next;
					prevNode->next->prev = tempHead;
					prevNode->next = tempHead;
					tempHead->prev = prevNode;
					tempHead->task->priority = newp;
					return;

				}
				if(prevNode == last){

					prevNode->next = tempHead;
					tempHead->prev = prevNode;
					tempHead->next = NULL;
					last = tempHead;
					tempHead->task->priority = newp;
					return;

				}
				return;

			}

			prevNode = prevNode->prev;

		}

		cout << "Entering fourth while" << endl;
		prevNode = first;
		while(prevNode != NULL){

			if(prevNode->task->priority > newp){

				if(prevNode != first){
					tempHead->next = prevNode;
					tempHead->prev = prevNode->prev;
					prevNode->prev->next = tempHead;
					prevNode->prev = tempHead;
					tempHead->task->priority = newp;
					return;
				}
				if(prevNode == first){
					tempHead->next = prevNode;
					prevNode->prev = tempHead;
					tempHead->prev = NULL;
					first = tempHead;
					tempHead->task->priority = newp;
					return;
				}
				return;

			}
			prevNode = prevNode->next;

		}

		// 1
		// 1
		// 2
		// 3
	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
		totmin += m;
		if (totmin >= 60) {
			int x = totmin%60;
			int y = totmin/60;
			totmin = x;
			tothrs += y;
		}
		tothrs += h;
	}

	void DLL::removeTime(int h, int m) {
		int tot = tothrs * 60 + totmin;
		int rem = h * 60 + m;
		tot -=rem;
		tothrs = tot/60;
		totmin = tot%60;
	}
	/********************End of Optional Helper Methods ********************/
