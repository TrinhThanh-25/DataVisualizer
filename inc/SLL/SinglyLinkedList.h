#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <vector>

#include "SLL/SLLNode.h"
#include "SLL/SLLArrow.h"
class SinglyLinkedList{
    public: 
        
    private:
        std::vector<SLLNode*> list;
        SLLNode* temp;

        SLLArrow head;
};

#endif