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

};


