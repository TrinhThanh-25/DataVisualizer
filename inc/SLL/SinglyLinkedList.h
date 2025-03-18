#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <vector>
#include <sstream>

#include "SLL/SLLNode.h"

enum class AnimationState {
    IDLE,       
    INSERTING,  
    DELETING,   
    SEARCHING,  
    UPDATING    
};

class SinglyLinkedList {
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void createList(std::string text);
        void insertNode(const int& index, int value);
        void updateInsertAnimation(const int& index);
        void removeNode(const int& index);
        void updateNode(const int& index, int value);
        void searchNode(int value);
        void clearList();

        int getListSize();

        void update();
        void draw();

    public:
        AnimationState animationState = AnimationState::IDLE;
        
    private:
        std::vector<SLLNode*> list;

        SLLArrow* head;
        SLLArrow* cur;
        bool isCreated = false;

        int animationStep = 0;
};

#endif