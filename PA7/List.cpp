//linked list for entire program
#include "List.hpp"
using std::cout;

template <typename T>
void List<T>::setpHead(T newData) {
	
	if (this->isEmpty()) {

		studentNode<T> newNode = new studentNode<T>;
		newNode.setNodeData(newData);

		this->pHead = newNode; //set head of list as new node
	}

	else {
		cout << "Head cannot be modified, list is already populated!";
	}

}

template<typename T>
studentNode<T>* List<T>::getpHead(void) {
	return this->pHead;
}

template<typename T>
bool List<T>::insertAtEnd(T newData)
{
	bool success = false;

	studentNode<T> newNode = new studentNode<T>;
	newNode.setNodeData(newData);

	if (newNode == nullptr) {
		success = false;
	}

	else {
		studentNode<T> pMem = this->getpHead();
		while (pMem.getNext() != nullptr) {
			pMem = pMem.getNext();
		}
		pMem.setNext(newNode);
		success = true;
	}
	return success;
}

template<typename T>
List<T>::List() {
	pHead = nullptr; 
	pTail = nullptr;
}

template <typename T>
List<T>::~List() {
	destroyList();
}

template<typename T>
bool List<T>::isEmpty() {
	return pHead == nullptr;
}

template<typename T>
void List<T>::destroyList() { //public ver. of destroy

		destroyList(pHead); //calls priv version

}

template<typename T>
List<T>::List(const List& rhs) //hard copy of entire list
{

	if (rhs.pHead== nullptr) {
		return;
	}

	studentNode<T>* pTemp = rhs.pHead;
	pHead = new studentNode<T>; //deep copy of rhs head
	pHead->setNodeData(pTemp->getNodeData());

	studentNode<T>* pCur = pHead;

	while (pTemp->getNext() != nullptr) {
		pTemp = pTemp->getNext();

		studentNode<T>* newNode = new studentNode<T>;
		newNode->setNodeData(pTemp->getNodeData());

		pCur->setNext(newNode);

		pCur = newNode;
	}

	pCur->setNext(nullptr); //sets very end to nullptr

}

template<typename T>
List<T>& List<T>::operator=(const List& rhs)
{
	
	List(rhs); //creates a shallow copy of rhs list
	return (*this); 

}

template<typename T> ///stinker >:(
void List<T>::destroyList(studentNode<T>* pHead) {
	if (pHead!= nullptr) { //checks before looping
		destroyList(pHead->getNext()); //recursively delete list
		delete pHead;
	}
}
