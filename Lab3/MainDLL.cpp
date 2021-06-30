#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "ToDoList.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	ToDoList *list = new ToDoList("ListofTasks.txt");
}

