#include "studentNode.hpp"
#include <iostream>

template <typename T>
class List {
private:
	//linked list has access to both head and tail (insert at tail though)
	studentNode<T>* pHead;
	studentNode<T>* pTail;


	void destroyList(studentNode<T>* pHead);

public: 

	List();
	~List();

	bool isEmpty();
	void destroyList();

	List(const List& rhs); //copy constructor
	List<T>& operator=(const List& rhs); //overloaded copy assignment


	//setters and getters for list components

	void setpHead(T newData);  //takes in new data to set head ptr
	studentNode<T>* getpHead(void);

	//dont need setters and getters for the tail -> that is what inserts are for!

	bool insertAtEnd(T newData); //should insert take in data or newnode?
	void printList(); 

};

//all class function definitions, because a cpp file doesn't work for templates.. i still dk why

template <typename T>
void List<T>::setpHead(T newData) {

	if (this->isEmpty()) {

		this->pHead = new studentNode<T>(newData);
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
	
	studentNode<T>* newNode = new studentNode<T>(newData);
	if (newNode == nullptr) {
		return false; // Memory allocation failed
	}

	if (isEmpty()) {
		pHead = pTail = newNode; // If the list is empty, set both head and tail to the new node
	}
	else {
		pTail->setNext(newNode); // Link the current tail to the new node
		pTail = newNode;         // Update the tail to point to the new node
	}

	success = true;
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
List<T>::List(const List& rhs) // Deep copy of rhs list
{
	if (rhs.pHead == nullptr) {
		pHead = nullptr;
		pTail = nullptr;
		return;
	}

	studentNode<T>* pTemp = rhs.pHead;
	pHead = new studentNode<T>(pTemp->getNodeData()); // Initialize head with the first element's data
	studentNode<T>* pCur = pHead;

	pTemp = pTemp->getNext();
	while (pTemp != nullptr) {
		studentNode<T>* newNode = new studentNode<T>(pTemp->getNodeData());
		pCur->setNext(newNode);
		pCur = newNode;
		pTemp = pTemp->getNext();
	}

	pTail = pCur; // Update the tail to the last node in the new list
}

template<typename T>
List<T>& List<T>::operator=(const List& rhs)
{
	if (this == &rhs) {
		return *this; // Prevent self-assignment
	}

	// Destroy existing list
	destroyList();

	// Perform deep copy of rhs list
	studentNode<T>* pTemp = rhs.pHead;
	if (pTemp == nullptr) {
		pHead = nullptr;
		pTail = nullptr;
		return *this;
	}

	pHead = new studentNode<T>(pTemp->getNodeData());
	studentNode<T>* pCur = pHead;

	pTemp = pTemp->getNext();
	while (pTemp != nullptr) {
		studentNode<T>* newNode = new studentNode<T>(pTemp->getNodeData());
		pCur->setNext(newNode);
		pCur = newNode;
		pTemp = pTemp->getNext();
	}

	pTail = pCur; // Set the tail
	return *this;
}

template<typename T> ///stinker >:(
void List<T>::destroyList(studentNode<T>* pHead) {
	if (pHead != nullptr) { //checks before looping
		destroyList(pHead->getNext()); //recursively delete list
		delete pHead;
	}
}

template<typename T>
void List<T>::printList() {
	// Start with the head node
	studentNode<T>* currentNode = pHead;
	cout << "Attendance list: " << endl;
	// Traverse the list and print each node's name
	while (currentNode != nullptr) {
		cout << currentNode->getNodeData().getName()<<"->"; // Assuming `getName()` exists in studentNode
		currentNode = currentNode->getNext(); // Move to the next node
	}
	cout << endl;
}

