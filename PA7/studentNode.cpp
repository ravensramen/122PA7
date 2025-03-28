#include "studentNode.hpp"

template<typename T>
studentNode<T>::studentNode(const studentNode &rhs)
{
	//why is this not letting me use setters on rhs?? RAHH

	//still works... i think
	this->setNodeData(rhs.data);
	this->setNext(rhs.pNext);
}

//setters and getters
template <typename T>
void studentNode<T>::setNodeData(T newData) {
	data = newData;
}

template<typename T>
T studentNode<T>::getNodeData(void) {
	return this->data;
}

template<typename T>
void studentNode<T>::setNext(studentNode<T>* newNext) {
	this->pNext = newNext;
}

template <typename T>
studentNode<T>* studentNode<T>::getNext(void) {
	return this->pNext;
}
