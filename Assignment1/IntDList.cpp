//This code defines the functions for implementing a doubly linked list that adds integers in ascending order

#include "IntDList_node.hpp"
#include "IntDList.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

IntDLList::IntDLList() //Constructor
{
    ListHead = new IntDLLNode(0, 0, 0);

    ListHead->next = ListHead;
    ListHead->prev = NULL;

}

IntDLList::~IntDLList() { //Destructor
    while(!isEmpty()) deleteFromHead();
}

void IntDLList::addToHead(int e) {
    IntDLLNode* u = new IntDLLNode(e, ListHead->next, ListHead);
    if (!isEmpty()) {
        IntDLLNode* v = ListHead->next;
        v->prev = u;
    }
    ListHead->next = u;
}

void IntDLList::insertInOrder(int e) {
    IntDLLNode* u = ListHead->next;
    if(isEmpty()) {
        addToHead(e);
    } else {
        while(e > u->info && u != ListHead) {
            u = u->next;
        }
        IntDLLNode* v = u->prev;
        IntDLLNode* w = new IntDLLNode(e, v->next, u->prev);
        v->next = u->prev = w;
    }
}

void IntDLList::addToTail(int e) {
    IntDLLNode* u = ListHead->next;
    while(u->next != ListHead) u = u->next;
    IntDLLNode* v = new IntDLLNode(e, u->next, u);
    u->next = v;
}

int IntDLList::deleteFromHead() {
    IntDLLNode* u = ListHead->next;
    IntDLLNode* v = u->next;
    ListHead->next = v;
    v->prev = ListHead;
    int w = u->info;
    delete u;
    return w;
}

int IntDLList::deleteFromTail() {
    IntDLLNode* u = ListHead->next;
    while(u->next != ListHead) u = u->next;
    IntDLLNode* v = u->prev;
    v->next = u->next;
    int w = u->info;
    delete u;
    return w;
}

void IntDLList::deleteNode(int e) {
    IntDLLNode* u = ListHead->next;
    while(u->info!=e) u = u->next;
    IntDLLNode* v = u->prev;
    IntDLLNode* w = u->next;
    v->next = w;
    w->prev = v;
    delete u;
}

bool IntDLList::isInList(int e) const {
    IntDLLNode* u = ListHead->next;
    while(u->info!=e) u = u->next;
    if (u!=NULL) return true;
    return false;
}

string IntDLList::addToString() const {
    IntDLLNode* u = ListHead->next;
    string a;
    while(u!=ListHead) {
        stringstream intToString;
        string b;
        intToString << u->info;
        intToString >> b;
        a = a+b;
        u = u->next;
    }
    return a;
}

// ******Used for quick testing during development; Program is run and tested with intDList.cpp using "g++ -std17=c++17 -Wall IntDList.cpp intDList_test.cpp" in terminal
// int main() {
//     IntDLList myList;
//     myList.insertInOrder(9);
//     myList.insertInOrder(8);
//     myList.insertInOrder(0);
//     myList.insertInOrder(3);
//     string output = myList.addToString();

//     myList.insertInOrder(4);
//     output = myList.addToString();

//     myList.deleteFromHead();
//     output = myList.addToString();

//     myList.deleteNode(8);
//     output = myList.addToString();
    
//     myList.deleteFromTail();
//     output = myList.addToString();
//     return 0;
// }
