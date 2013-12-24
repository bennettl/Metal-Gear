
#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <class T>

class Linkedlist {
    protected:
        Node<T>* head;
        int length;
    public:
        // Constructor
        Linkedlist(){
            head   = NULL;
            length = 0;
        }
        // Return top of list
        int begin(){
            return 0;
        }
        // Return size
        int size(){
            return length;
        }
      
        // Retrieve object at index
        T at(int listIndex){        
            // If index is 0, remove the head, else keep going through the list until the listIndex is equal to one
            if (listIndex == 0){
                return head->data;
            } else if (listIndex < length){
                for (Node<T> *current = head; current != NULL ; current = current->next){
                    if (listIndex == 1){
                        return current->next->data;
                        break;
                    }
                    listIndex--;
                }
            }
            return NULL;
        }
      
        // Inserts to list at an index
        void insert(int listIndex, T value){
            // Create a new node
            Node<T> * newNode = new Node<T>(value);
            
            if (listIndex == 0 && head == NULL){
                head = newNode;
            }
            for (Node<T>* current = head; current != NULL; current = current->next){
                // Reset where the previous and new node is pointing to
                if (listIndex == 1){
                    newNode->next = current->next;
                    current->next = newNode;
                    break;
                }
                listIndex--;
            }
            length++;
        }
        // Pushes object to botton of list
        void push_back(T Object){
            this->insert(length,Object);
        }
        
        // Erases object at certain index
        void eraseObj(int listIndex){
            Node<T> * nextNode = NULL;
            
            // If index is 0, remove the head, else keep going through the list until the listIndex is equal to one
            if (listIndex == 0){
                nextNode = head->next;
                delete head;
                head = nextNode;
                length--;
            } else if (listIndex < length){
                for (Node<T> *current = head; current != NULL ; current = current->next){
                    
                    if (listIndex == 1){
                        nextNode = current->next->next;
                        delete (current->next);
                        current->next = nextNode;
                        break;
                    }
                    
                    listIndex--;
                }
                length--;
            }
        }
        
        // Go backwards from the linked list and erase every element
        void clearList(){
            for (int i = length -1 ; i > -1; i--) {
                this->eraseObj(i);
            }
        }
};

#endif
