//Structure of nodes in DLinkedList

#ifndef D_NODE_H
#define D_NODE_H

template <typename E> class DNode {
    public:
        DNode() {}

    private:
        E elem;
        DNode<E> *next;
        DNode<E> *prev;

    template<typename T> friend class DLinkedList;

};
#endif