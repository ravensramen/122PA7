#include <stack>
#include <iostream>
#include "AttendanceTracker.hpp"

using std::stack;
using std::string;
using std::deque;
using std::string;

// Template class for absence stack
template<class T, class Container = std::deque<T>>
class absenceStack {
private:
    std::stack<T, Container> container;  // The stack container

public:
    // Push an absence (date) onto the stack
    void pushAbsence(const T& date) {
        container.push(date);
    }

    // Pop the top absence from the stack
    void popAbsence() {
        if (!container.empty()) {
            container.pop();  // Removes the top of the stack
        }
        else {
            std::cout << "Error: Stack is empty, cannot pop absence." << std::endl;
        }
    }

    // Get the top absence date without removing it from the stack
    T topAbsence() const {
        if (!container.empty()) {
            return container.top();  // Returns the top element
        }
        else {
            throw std::out_of_range("Error: Stack is empty.");
        }
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return container.empty();
    }

    // Get the number of elements in the stack
    int size() const {
        return container.size();
    }

    // Clear the stack
    void clear() {
        while (!container.empty()) {
            container.pop();  // Pop all elements
        }
    }

    // For debugging purposes: Print all absences in the stack
    void printStack() const {
        if (container.empty()) {
            std::cout << "The absence stack is empty." << std::endl;
        }
        else {
            std::stack<T, Container> tempStack = container;  // Create a copy of the stack
            while (!tempStack.empty()) {
                std::cout << tempStack.top() << std::endl;  // Print the top element
                tempStack.pop();  // Remove the top element
            }
        }
    }

    // Function to copy the stack to another stack (for saving or processing)
    stack<T, Container> copy() const {
        return container;  // Return the current stack (copy will be made in the calling method)
    }

    // Function to reverse the stack contents
    stack<T, Container> reverse() const {
        stack<T, Container> reversedStack;
        stack<T, Container> tempStack = container;  // Temporary copy of the original stack

        // Reverse the elements of the stack into the new stack
        while (!tempStack.empty()) {
            reversedStack.push(tempStack.top());  // Push elements into reversed stack
            tempStack.pop();
        }

        return reversedStack;  // Return the reversed stack
    }

    // Overloaded copy assignment operator
    absenceStack<T, Container>& operator=(const absenceStack<T, Container>& other) {
        if (this == &other) {  // Check for self-assignment
            return *this;
        }

        // Clear the current stack before copying
        container = other.container;  // Simply assign the container (stack) from the other object

        return *this;
    }
};