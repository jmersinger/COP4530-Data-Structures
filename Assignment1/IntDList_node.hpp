//           Doubly-linked list class to store integers
#ifndef INTDLISTNODE_H
#define INTDLISTNODE_H
class IntDLLNode 
{
public:
    int info;
    class IntDLLNode *next;
    class IntDLLNode *prev;

    IntDLLNode(int el, IntDLLNode *ptr1 = 0, 
                       IntDLLNode *ptr2 = 0) 
    {
        info = el; 
        next = ptr1; 
        prev = ptr2;
    }
};
#endif /* INTDLISTNODE_H */