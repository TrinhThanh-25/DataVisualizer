#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <vector>

#include "SLL/SLLNode.h"
#include "SLL/SLLArrow.h"
class SinglyLinkedList{
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void insertNode(const int& index, int value);
        void removeNode(const int& index);
        void update();
        void draw();
        
    private:
        std::vector<SLLNode*> list;
        SLLNode* temp;

        SLLArrow* head;
};

#endif