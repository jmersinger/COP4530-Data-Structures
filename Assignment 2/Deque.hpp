//Deque implemented into NotationConverter.hpp for class methods

#ifndef DEQUE_H
#define DEQUE_H

#include "DLinkedList.hpp"

//Dequeue Empty Exception
class DequeEmpty : public std::runtime_error {
    public:
        DequeEmpty(const std::string& err) : std::runtime_error(err) {};
};

//Initializations
template <typename E> class Deque {

    public:
        #include "DLinkedList.hpp"

        Deque() {};
        int size() const {return n;};
        bool empty() const {return D.isEmpty();};

        const E &front() const;
        const E &back() const;

        void insertFront(const E &e);
        void insertBack(const E &e);

        void removeFront();
        void removeBack();

        private:
        DLinkedList<E> D;
        int n = 0;
};


//Function Definitions

template <typename E> const E& Deque<E>::front() const {
    if(empty()) {throw DequeEmpty("Deque is empty.");}
    return D.front();
}

template <typename E> const E& Deque<E>::back() const {
    if(empty()) {throw DequeEmpty("Deque is empty.");}
    return D.back();
}

template <typename E> void Deque<E>::insertFront(const E &e) {
    D.addFront(e);
    n++;
}

template <typename E> void Deque<E>::insertBack(const E &e) {
    D.addBack(e);
    n++;
}

template <typename E> void Deque<E>::removeFront() {
    if(empty()) {throw DequeEmpty("Deque is empty.");}
    D.removeFront();
    n--;
}

template <typename E> void Deque<E>::removeBack() {
    if(empty()) {throw DequeEmpty("Deque is empty.");}
    D.removeBack();
    n--;
}

#endif