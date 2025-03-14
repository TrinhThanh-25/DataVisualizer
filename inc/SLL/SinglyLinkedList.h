#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <vector>

#include "SLL/SLLNode.h"
#include "SLL/SLLArrow.h"

class SinglyLinkedList{
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void createList(std::string text);
        void insertNode(const int& index, int value);
        void removeNode(const int& index);
        void updateNode(const int& index, int value);
        void searchNode(int value);
        void clearList();

        int getListSize();

        void update();
        void draw();
        
    private:
        std::vector<SLLNode*> list;
        SLLNode* temp;

        SLLArrow* head;

        bool isCreated=false;
};

#endif