#include "ToDoList.hpp"

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

ToDoList::ToDoList() {
	list = new DLL();
	readList("ListofTasks.txt");
	list->printList();
	cout << endl;
	interface();
}

ToDoList::ToDoList(string s) {
	list = new DLL();
	readList(s);
	list->printList();
	cout << endl;
	interface();
}

void ToDoList::interface() {
	int choice=0;
	while (choice != 8) {
		cout << "What do you want to do?" <<endl<< flush;
		cout <<"Enter:" << endl<< flush;
		cout <<"\t1 for adding a task"<<endl<< flush;
		cout <<"\t2 for removing a task" << endl<< flush;
		cout <<"\t3 for moving a task up in the list" << endl<< flush;
		cout <<"\t4 for moving a task down in the list" << endl<< flush;
		cout <<"\t5 for changing the priority of a task" << endl<< flush;
		cout <<"\t6 for getting a list of tasks with priority p"<< endl<<flush;
		cout <<"\t7 for printing the list "<<endl<<flush;
		cout <<"\t8 for exit" <<endl<< flush;

		cin >> choice;
		if (choice ==1) {
			addTask();
		}
		else if (choice == 2) {
			removeTask();
		}
		else if (choice == 3) {
			moveUp();
		}
		else if (choice == 4) {
			moveDown();
		}
		else if (choice ==5) {
			changePriorityofTask();
			list->printList();
		}

		else if (choice ==6){
			getPriorityTasks();
		}
		else if (choice == 7) {
			list->printList();
		}
		else if (choice == 8) {
			ByeNow();
		}
	}
}


void ToDoList::changePriorityofTask() {
	cout<<"Changing a Task's Priority:" <<endl;
	cout << "Enter the task number:" <<endl << flush;
	int tnum;
	cin >> tnum;
	cout << "Enter the task's new priority" << endl<< flush;
	int pnum;
	cin >> pnum;

	if (tnum >0 && pnum > 0) {
		list->changePriority(tnum,pnum);
		list->printList();
	}

}

void ToDoList::getPriorityTasks() {
	int mintot = 0;
	int hrtot = 0;
	cout << "Enter the priority you want: "<<endl;
	int prio;
	cin >> prio;
	list->listDuration(&hrtot, &mintot,prio);
	cout << "The total time needed to complete tasks of priority "<<prio<<" is ";
	cout << hrtot<<":"<<mintot<<endl;
	cout << endl<<flush;
	list->printList(prio);
	return;
}


void ToDoList::moveUp() {
	cout<<"Moving a Task Up:" <<endl;
	cout << "Enter the task number:" <<endl << flush;
	int tnum;
	cin >> tnum;

	if (tnum >0) {
		list->moveUp(tnum);
		list->printList();
	}
}
string ToDoList::getTitle() {
	string str = "";
	while (str == "") {
	    getline(cin, str);
	}
	string title;
	title = strip(str);
	return title;

}
void ToDoList::moveDown() {
	cout<<"Moving a Task Down:" <<endl;
	cout << "Enter the task number:" <<endl << flush;
	int tnum;
	cin >> tnum;

	if (tnum >0) {
		list->moveDown(tnum);
		list->printList();
	}
}
void ToDoList::removeTask() {
	cout<<"Removing a task:" <<endl;
	cout << "Enter the number of the task you wish to remove" <<endl << flush;
	int tnum;
	cin >> tnum;

	if (tnum >0) {
		list->remove(tnum);
		cout << "Did you complete the task (yes or no)?" << endl << flush;
		string s;
		cin >> s;
		if (s == "yes") {
			cout << "WOO WOO!!!  One less thing to do!!!" << endl;
		}
		list->printList();
	}
}

void ToDoList::addTask() {
	cout<<"Adding a task:" <<endl;
	cout << "Enter the task as follows: task, priority, hrs:mins" <<endl << flush;
	string taskstr = "";
    while (taskstr == "") {
    	getline(cin, taskstr);
    }
	string task;
	task = strip(taskstr);
	string pris;
	string hrs;
	string mins;
	pris = strip(taskstr);
	int prio = 0;
	stringstream tmp(pris);
	tmp>>prio;
	hrs = strip(taskstr);
	int hr = 0;
	stringstream tmp2(hrs);
	tmp2>>hr;
	mins = taskstr;
	stringstream tmp3(mins);
	int min = 0;
	tmp3>>min;
	cout << task<<":::"<<pris<<":::"<<hrs<<":::"<<mins<<":::"<<endl;
	if (task.length() >0) {
		list->push(task,prio,hr,min);
		list->printList();
	}

}
void ToDoList::ByeNow() {
	cout << "Bye Now!" << endl;
	return;
}

string ToDoList::strip(string &s) {
	const char* WhiteSpace = " \t\v\r\n";
	size_t start = s.find_first_not_of(WhiteSpace);
	const char* EndChar = ":,\n";
	size_t end = s.find_first_of(EndChar);
	string s2;
	int len = s.length();
	if (start<end){
		s2=s.substr(start,end-start);
		s = s.substr(end+1,len-end+1);
	}
	return s2;

}
void ToDoList::readList(string f) {
	ifstream file(f.c_str());
	string taskstr;
	string task;
	string pris;
	string mins;
	string hrs;
	while (!file.eof()) {
		getline(file,taskstr);
		cout << taskstr<<endl;
		task = strip(taskstr);
		pris = strip(taskstr);
		int prio = 0;
		stringstream tmp(pris);
		tmp>>prio;
		hrs = strip(taskstr);
		int hr = 0;
		stringstream tmp2(hrs);
		tmp2>>hr;
		mins = taskstr;
		stringstream tmp3(mins);
		int min = 0;
		tmp3>>min;

		cout << task<<":::"<<pris<<":::"<<hrs<<":::"<<mins<<":::"<<endl;
		if (task.length() >0) {
			list->push(task,prio,hr,min);
		}
	}
	cout <<"*********DONE READING**************************"<<endl<<endl;
	return;
}



