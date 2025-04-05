#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include "studentData.hpp"  // Assuming the Data class is used to store student info
template <typename T>
class studentNode {
private:
    T data;
    studentNode<T>* pNext;

public:
    // Default constructor
    studentNode() : pNext(nullptr) {}

    // Constructor with data
    studentNode(T newData) : data(newData), pNext(nullptr) {}

    // Copy constructor
    studentNode(const studentNode& rhs) {
        this->setNodeData(rhs.data);
        this->setNext(rhs.pNext);
    }

    // Getter for data
    T& getNodeData() {
        return data;
    }

    // Setter for data
    void setNodeData(T newData) {
        data = newData;
    }

    // Getter for next pointer (const version)
    studentNode<T>* getNext() const {
        return pNext;
    }

    // Setter for next pointer
    void setNext(studentNode<T>* newNext) {
        pNext = newNext;
    }
};

#endif // STUDENTNODE_H