#include "SLL/SinglyLinkedList.h"
#include <sstream>

SinglyLinkedList::SinglyLinkedList() : head(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f})){
    head->setTarget({head->getPosition().x+ArrowLength,head->getPosition().y});
    head->setLabel("head");
    head->setNull();
}

SinglyLinkedList::~SinglyLinkedList() {
    clearList();
    delete head;
}

void SinglyLinkedList::createList(std::string text){
    clearList();
    isCreated=true;
    std::string value;
    std::stringstream ss(text);
    int i=0;
    while (std::getline(ss, value, ',')) {
        insertNode(i++,std::stoi(value));
    }
}

void SinglyLinkedList::insertNode(const int& index, int value) {
    if(!isCreated) isCreated=true;
    SLLNode* newNode = new SLLNode();
    newNode->setValue(value);
    list.insert(list.begin()+index,newNode);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
}

void SinglyLinkedList::removeNode(const int& index) {
    if (index < 0 || index >= list.size()) return;
    delete list[index];
    list.erase(list.begin() + index);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
}

void SinglyLinkedList::updateNode(const int &index,int value){
    list[index]->setValue(value);
}

void SinglyLinkedList::searchNode(int value){}

void SinglyLinkedList::clearList(){
    for (auto node : list) {
        delete node;
    }
    list.clear();
    isCreated=false;
}

int SinglyLinkedList::getListSize(){
    return list.size();
}

void SinglyLinkedList::update(){
    if(list.empty()){
        head->setTarget({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    head->update();
    if (!list.empty()) {
        head->setTarget(list[0]->getStartPos());
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->updateCur(list[index + 1]->getStartPos());
        }
        list[list.size() - 1]->updateCur({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::draw(){
    if(isCreated)
        head->draw();
    for (auto node : list) {
        if (!node) continue;
        node->drawCur();
    }
}

