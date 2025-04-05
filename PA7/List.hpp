
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include "studentNode.hpp"  // Assuming you have a Data class for student data

// Node structure to hold data and the link to the next node
template <typename T>
struct studentNode {
    T data;
    studentNode* next;

    studentNode(const T& d) : data(d), next(nullptr) {}
};

// List class to manage the linked list of students
template <typename T>
class List {
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List() { destroyList(); }

    // Insert data at the end of the list
    void insertAtEnd(const T& data) {
        studentNode<T>* newNode = new studentNode<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get the head pointer of the list
    studentNode<T>* getpHead() const {
        return head;
    }

    // Destroy the list by deallocating memory
    void destroyList() {
        studentNode<T>* current = head;
        while (current != nullptr) {
            studentNode<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Print the list (useful for debugging)
    void printList() const {
        studentNode<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << std::endl;  // Assuming Data class has an overloaded operator<<
            current = current->next;
        }
    }

private:
    studentNode<T>* head;  // Pointer to the first node
    studentNode<T>* tail;  // Pointer to the last node
    int size;  // Size of the list
};

#endif // LIST_H