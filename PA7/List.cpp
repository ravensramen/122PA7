//linked list for entire program
#include "List.hpp"

template <typename T>
void List<T>::setpHead(studentNode<T>* newHead) {
	this->pHead = newHead;
}

template<typename T>
studentNode<T>* List<T>::getpHead(void) {
	return this->pHead;
}

template<typename T>
List<T>::List() {
	pHead = nullptr; 
}

template <typename T>
List<T>::~List() {
	this->destroyList();
}

template<typename T>
bool List<T>::isEmpty() {
	return pHead == nullptr;
}

template<typename T>
void List<T>::destroyList() { //public ver. of destroy
	destroyList(this->getpHead());
}

template<typename T>
void List<T>::destroyList(studentNode<T>* pHead) {
	if (pHead != nullptr) {
		destroyList(pHead->getNext()); //recursively delete list
		delete pHead;
	}
}
