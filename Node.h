#ifndef Node_type
#define Node_type

#include	"LibStudent.h"

typedef LibStudent type;

struct Node{
	type item;
	Node *next;
	Node(type);
};


#endif