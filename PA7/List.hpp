
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include "studentNode.hpp"  // Assuming you have a Data class for student data

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
            
            tail->setNext(newNode);
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
            studentNode<T>* next = current->getNext();
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Print the list (useful for debugging) //FIX ME RAAAH
    void printList() const {
        studentNode<T>* current = head;
        while (current != nullptr) {
            
            current = current->getNext();
        }
    }

private:
    studentNode<T>* head;  // Pointer to the first node
    studentNode<T>* tail;  // Pointer to the last node
    int size;  // Size of the list
};

#endif // LIST_H