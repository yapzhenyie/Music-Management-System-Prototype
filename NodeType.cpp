#ifndef NODETYPE_CPP
#define NODETYPE_CPP

#include <iostream>

using namespace std;

template <class T>
class NodeType {
public:
	T* data;
	string identifier;
	NodeType<T>* node;
};
#endif