#include "studentNode.hpp"

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

	//setters and getters for list components

	void setpHead(studentNode<T>* newHead); //need seperate funct for insert at front (for ptrs)
	studentNode<T>* getpHead(void);

	//dont need setters and getters for the tail -> that is what inserts are for!

};


