
#ifndef Node_h
#define Node_h

#include <cstddef>

template <class T>

class Node{
    public:
        T data;
        Node<T>* next;
        // Constructor
        Node(T value){
            data = value;
            next = NULL;
        }
};

#endif
