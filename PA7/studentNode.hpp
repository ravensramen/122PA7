#include "studentData.hpp"

//uses template type, node for each student

template <typename T>

class studentNode {
private:
	T data; //template for data stored, will be of "Data" class type from studentData.hpp
	studentNode<T>* pNext; //pointer to next node, contains data "T"

public:
	//default constructor and destructor
	studentNode();
	~studentNode();

	//copy constructor, this function must be declared in header (idk why, doesn't work otherwise)
	studentNode(const studentNode &rhs);


	//setters and getters
	void setNodeData(T newData);
	T getNodeData(void);

	void setNext(studentNode<T>* newNext);
	studentNode<T>* getNext(void);
};