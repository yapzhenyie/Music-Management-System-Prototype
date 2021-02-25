#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

#include "NodeType.cpp"

using namespace std;

template <class T>
class LinkedList {
private:
	NodeType<T>* head;
	int size = 0;
public:
	NodeType<T>* getHead();
	void add(T* data);
	void remove(T* data);
	bool contains(T* data);
	T* get(string title);
	T* get(int index);
	void clear();
	int getSize();
};
#endif
