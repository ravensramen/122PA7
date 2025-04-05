#include <stack>
#include <iostream>
#include "AttendanceTracker.hpp"

using std::stack;
using std::string;
using std::deque;
using std::string;

// template class for absence stack, using std::stack
template<class T, class Container = std::deque<T>>
class absenceStack {
private:
    std::stack<T, Container> container;  // the stack container

public:
    // push an absence (date) onto the stack
    void pushAbsence(const T& date) {
        container.push(date);
    }

    // pop the top absence from the stack
    void popAbsence() {
        if (!container.empty()) {
            container.pop();  
        }
        else {
            std::cout << "Error: Stack is empty, cannot pop absence!" << std::endl;
        }
    }

    // get the top absence date without removing it from the stack
    T topAbsence() const {
        if (!container.empty()) {
            return container.top();  
        }
        else {
            throw std::out_of_range("Error: Stack is empty.");
        }
    }

    // check if the stack is empty
    bool isEmpty() const {
        return container.empty();
    }

    // get the number of elements in the stack
    int size() const {
        return container.size();
    }

    // clear the stack
    void clear() {
        while (!container.empty()) {
            container.pop();  
        }
    }

    // for debugging purposes: print all absences in the stack
    void printStack() const {
        if (container.empty()) {
            std::cout << "The absence stack is empty." << std::endl;
        }
        else {
            std::stack<T, Container> tempStack = container;  // create a copy of the stack
            while (!tempStack.empty()) {
                std::cout << tempStack.top() << std::endl;  // print the top element
                tempStack.pop();  // remove the top element
            }
        }
    }

    // function to copy the stack to another stack (for saving or processing)
    stack<T, Container> copy() const {
        return container; 
    }

    // function to reverse the stack contents
    stack<T, Container> reverse() const {
        stack<T, Container> reversedStack;
        stack<T, Container> tempStack = container;  // temporary copy of the original stack

        // reverse the elements of the stack into the new stack
        while (!tempStack.empty()) {
            reversedStack.push(tempStack.top());  // push elements into reversed stack
            tempStack.pop();
        }

        return reversedStack;  // return the reversed stack
    }

    // overloaded copy assignment operator
    absenceStack<T, Container>& operator=(const absenceStack<T, Container>& other) {
        if (this == &other) {  // check for self-assignment
            return *this;
        }

        // clear the current stack before copying
        container = other.container;  

        return *this;
    }
};