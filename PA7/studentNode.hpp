#include "studentData.hpp"  

//class for each node

template <typename T>
class studentNode {
private:
    T data;
    studentNode<T>* pNext;

public:
    studentNode() : pNext(nullptr) {}

    studentNode(T newData) : data(newData), pNext(nullptr) {}

    T& getNodeData() {
        return data;
    }

    void setNodeData(T newData) {
        data = newData;
    }

    studentNode<T>* getNext() const {
        return pNext;
    }

    void setNext(studentNode<T>* newNext) {
        pNext = newNext;
    }
};