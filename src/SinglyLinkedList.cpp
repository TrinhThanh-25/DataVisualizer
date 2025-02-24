#include "SLL/SinglyLinkedList.h"
#include <iostream>

SinglyLinkedList::SinglyLinkedList() : head(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f})){
    head->setTarget({head->getPosition().x+SLLArrowLength,head->getPosition().y});
    head->setLabel("head");
    head->setNull();
}

SinglyLinkedList::~SinglyLinkedList() {
    for (auto node : list) {
        delete node;
    }
    delete head;
}

void SinglyLinkedList::insertNode(const int& index, int value) {
    SLLNode* newNode = new SLLNode();
    newNode->setValue(value);
    list.insert(list.begin()+index,newNode);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+SLLArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
}

void SinglyLinkedList::removeNode(const int& index) {
    if (index < 0 || index >= list.size()) return;
    delete list[index];
    list.erase(list.begin() + index);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+SLLArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
}

void SinglyLinkedList::update(){
    if(!list.empty()){
        head->setTarget(list[0]->getStartPos());
    }
    else{
        head->setTarget({head->getPosition().x+200,head->getPosition().y});
        
    }
    head->update();
    if (!list.empty()) {
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->updateCur(list[index + 1]->getStartPos());
        }
        list[list.size() - 1]->updateCur({list[list.size() - 1]->getEndPos().x + SLLArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::draw(){
    head->draw();
    for (auto node : list) {
        if (!node) continue;
        node->drawCur();
        const char* txt = std::to_string(node->getValue()).c_str();
        DrawText(txt, node->getPosition().x + SLLNodeSize.x / 2.0f - MeasureText(txt, 16) / 2.0f, node->getPosition().y + SLLNodeSize.y / 2.0f - 8.0f, 16, BLACK);
    }
}

