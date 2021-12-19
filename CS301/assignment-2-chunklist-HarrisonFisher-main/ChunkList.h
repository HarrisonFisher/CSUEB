//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_driver.cpp for an example of how they are used.
class InvalidArrayLength{
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.

template<class T>
class ChunkList {
public:
    // Constructors

    /*
     * Function: Default Constructor
     *
     * Precondition: none
     *
     * Post-condition: none
     */
    ChunkList();

    /*
     * Function:  Constructs a ChunkList using the values from arr
     *
     * Precondition: Array Length should be bigger than 0
     *
     * Post-condition: Will throw if arrLen is less than or equal to 0
     */
    ChunkList(T arr[], int arrLen);
    ////////////////////////////////////////////////////////////////
    // Deconstructor

    /*
     * Function: De-Constructor
     *
     * Precondition: none
     *
     * Post-condition: none
     */
    ~ChunkList();
    ////////////////////////////////////////////////////////////////
    // Add/remove elements

    /*
     * Function: Ads value to list
     *
     * Precondition:
     * none
     *
     * Post-condition:
     * If empty list it will create new head
     * If the tail is full it will add a new tail
     *
     */
    void Append(T value);

    /*
     * Function:
     * Removes value in list
     *
     * Precondition:
     * The list is not empty
     *
     * Post-condition:
     * Will throw if the list is empty
     */
    void Remove(T value);
    ////////////////////////////////////////////////////////////////
    // Stuff to find out about the ChunkList

    /*
     * Function: Returns the length of the list
     *
     * Precondition: none
     *
     * Post-condition: none
     */
    int GetLength();

    /*
     * Function: Tells us what percentage of the ChunkList is actually storing items
     *
     * Precondition: none
     *
     * Post-condition: none
     */
    double LoadFactor();

    /*
     * Function:
     * Checks if the value is in the list
     *
     * Precondition:
     * none
     *
     * Post-condition:
     * if value found in list it will return true
     */
    bool Contains(T value);

    ////////////////////////////////////////////////////////////////
    // Accessing elements

    /*
     * Function: Searches the value of the index
     *
     * Precondition:
     * Input is greater than 0
     * Input is not bigger than the list length
     * The head is not null
     *
     * Post-condition:
     * Will throw if I < 0 or if I > listlen
     * Will throw if head is nullptr
     */
    T GetIndex(int i);


    /*
     * Function: Resets the iterator
     *
     * Precondition: none
     *
     * Post-condition: none
     */
    void ResetIterator();

    /*
     * Function: returns current item and moves Iterator to next item
     *
     * Precondition: none
     *
     * Post-condition:
     * Supposed to throw if it can no longer iterate
     *
     */
    T GetNextItem();
    ////////////////////////////////////////////////////////////////
    /*
     * Function: Checks if the list is empty
     *
     * Precondition: none
     *
     * Post-condition: if listLen==0 is true it will return true
     */
    bool IsEmpty();
private:

    // Note we did not need to make this a template
    // since this struct is part of a template class.
    struct Node {
        Node* next;
        int len;
        T values[ARRAY_SIZE];
    };

    Node* head;
    Node* tail;

    // iterator
    Node* iterNode;     // What node are were currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};




#include "ChunkList.cpp"

#endif //CHUNKLIST_H
