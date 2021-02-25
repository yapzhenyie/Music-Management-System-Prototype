#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "LinkedList.h"

using namespace std;

template<typename T>
NodeType<T>* LinkedList<T>::getHead() {
	return this->head;
}

template<typename T>
void LinkedList<T>::add(T* data) {
	NodeType<T>* newNode = new NodeType<T>;
	newNode->data = data;
	newNode->identifier = data->getIdentifier();
	newNode->node = NULL;

	if (head == NULL) {
		head = newNode;
	} else {
		NodeType<T>* last = head;
		while (last->node != NULL)
			last = last->node;
		last->node = newNode;
	}
	size++;
}

template <class T>
void LinkedList<T>::remove(T* data) {
	if (head != NULL) {
		NodeType<T>* current = head;
		while (current->node != NULL) {
			if (current->node->data == data) {
				NodeType<T>* toBeDeleted = current->node;
				current->node = current->node->node;
				delete toBeDeleted;
				size--;
				break;
			}
			current = current->node;
		}
		if (head->data == data) {
			NodeType<T>* toBeDeleted = head;
			if (head->node != NULL) {
				head = head->node;
			} else {
				head = NULL;
			}
			delete toBeDeleted;
			size--;
		}
	}
}

template <class T>
bool LinkedList<T>::contains(T* data) {
	if (head == NULL) {
		return false;
	}
	NodeType<T>* current = head;
	while (current != NULL) {
		if (current->data == data) {
			return true;
		}
		current = current->node;
	}
	return false;
}

template <class T>
T* LinkedList<T>::get(string title) {
	if (head == NULL) {
		return NULL;
	}
	NodeType<T>* current = head;
	while (current != NULL) {
		if (current->identifier == title) {
			return current->data;
		}
		current = current->node;
	}
	return NULL;
}

template <class T>
T* LinkedList<T>::get(int index) {
	if (index < 0 || index >= size) {
		cout << "Index out of bound." << endl;
		abort();
	}

	NodeType<T>* current = head;
	for (int i = 0; i < index; i++) {
		current = current->node;
	}
	return current->data;
}

template <class T>
void LinkedList<T>::clear() {
	NodeType<T>* current = head;
	while (head != NULL) {
		current = current->node;
		delete head;
		head = current;
	}
	size = 0;
}

template <class T>
int LinkedList<T>::getSize() {
	return this->size;
}
#endif