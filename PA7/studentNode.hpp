#ifndef STUDENTNODE_HPP
#define STUDENTNODE_HPP

//note for future self: i kept getting constructor errors with the list, after a couple
//hours i discovered template definitions must be in header :')

//constructor available across files
//template <typename T>
//studentNode<T>* newStudentNode(T newData) { return new studentNode<T>(newData); }

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

#endif // STUDENTNODE_HPP