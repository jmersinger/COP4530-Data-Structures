//Structure of DLinkedList used to implement Deque

#ifndef D_LINKED_LIST_H
#define D_LINKED_LIST_H

#include "DNode.hpp"
#include <iostream>
#include <string>

//Initialize DLL

template <typename E> class DLinkedList {

    public:
        DLinkedList();
        ~DLinkedList();
        bool isEmpty() const;
        const E &front() const;
        const E &back() const;

        void addFront(const E &e);
        void addBack(const E &e);

        void removeFront();
        void removeBack();

        void print() const;
        int getSize() const {return nElem;}

    private:
        DNode<E> *header;
        DNode<E> *trailer;
        int nElem = 0;
    
    protected:
        void add(DNode<E> *v, const E &e);
        void remove(DNode<E> *v);
};

//Function Definitions

template <typename E> DLinkedList<E>::DLinkedList() {
    header = new DNode<E>;
    trailer = new DNode<E>;

    header->next = trailer;
    trailer->prev = header;
}

template <typename E> bool DLinkedList<E>::isEmpty() const {
    return header->next == trailer;
}

template <typename E> const E& DLinkedList<E>::front() const {
    return header->next->elem;
}

template <typename E> const E& DLinkedList<E>::back() const {
    return trailer->prev->elem;
}

//add() inserts new node before "v"
template <typename E> void DLinkedList<E>::add(DNode<E> *v, const E &e) {
    DNode<E> *u = new DNode<E>;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    u->prev->next = u;
    v->prev = u;

    nElem++;
}

template <typename E> void DLinkedList<E>::remove(DNode<E> *v) {
    DNode<E> *u = v->prev;
    DNode<E> *w = v->next;
    u->next = w;
    w->prev = u;

    delete v;
    nElem--;
}

template <typename E> void DLinkedList<E>::addFront(const E &e) {
    add(header->next, e);
}

template <typename E> void DLinkedList<E>::addBack(const E &e) {
    add(trailer, e);
}

template <typename E> void DLinkedList<E>::removeFront() {
    remove(header->next);
}

template <typename E> void DLinkedList<E>::removeBack() {
    remove(trailer->prev);
}

template <typename E> DLinkedList<E>::~DLinkedList() {
    while(!isEmpty()) {removeFront();}
    delete header;
    delete trailer;
}

template <typename E> void DLinkedList<E>::print() const {
    DNode<E> *curr = header->next;
    while(curr != trailer) {
        std::cout << curr->elem << " ";
        curr = curr ->next;
    }
    std::cout << std::endl;
}

#endif