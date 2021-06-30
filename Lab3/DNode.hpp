#ifndef DNODE_HPP_
#define DNODE_HPP_
#include <stdlib.h>
using namespace std;

#include "Task.hpp"

class DNode {
	friend class DLL;
	Task *task;
	DNode *prev;
	DNode *next;
public:
	DNode();
	DNode(string t, int p, int lenhr, int lenmin);
};



#endif /* DNODE_HPP_ */
