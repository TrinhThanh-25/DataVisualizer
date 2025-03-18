#include "SLL/SinglyLinkedList.h"
#include <sstream>

SinglyLinkedList::SinglyLinkedList() : head(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f})), cur(new SLLArrow({SLLposition.x-50,SLLposition.y+100})){
    head->setTarget({head->getPosition().x+ArrowLength,head->getPosition().y});
    head->setLabel("head");
    head->setNull();
    cur->setLabel("cur");
    cur->setNull();
    cur->setDestination({SLLposition.x-50+ArrowLength,SLLposition.y+100});
    
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
    int index=0;
    while (std::getline(ss, value, ',')) {
        int val=stoi(value);
        SLLNode* newNode = new SLLNode();
        newNode->setValue(val);
        list.insert(list.begin()+index,newNode);
        for (int i=index;i<list.size();i++){
            list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
            list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
        }
    }
    if(list.empty()){
        head->setTarget({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    head->update();
    if (!list.empty()) {
        head->setTarget(list[0]->getStartPos());
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTarget(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTarget({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::insertNode(const int& index, int value) {
    if(!isCreated) isCreated=true;
    SLLNode* newNode = new SLLNode();
    newNode->setValue(value);
    list.insert(list.begin()+index,newNode);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
        list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
    for (int i = index; i < list.size() - 1; i++) {
        list[i]->setDestination(list[i + 1]->getStartPos());
        list[i]->updateCur();
    }
    list[list.size()-1]->setDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
    list[list.size() - 1]->updateCur();
    list[list.size() - 1]->setNull();
    update();
}

void SinglyLinkedList::updateInsertAnimation(const int& index){
    if (animationState == AnimationState::IDLE) return;
    
}

void SinglyLinkedList::removeNode(const int& index) {
    if (index < 0 || index >= list.size()) return;
    delete list[index];
    list.erase(list.begin() + index);
    for (int i=index;i<list.size();i++){
        list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
        list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
    }
    if(list.empty()) return;
    for (int i = index; i < list.size() - 1; i++) {
        list[i]->setDestination(list[i + 1]->getStartPos());
        list[i]->updateCur();
    }
    list[list.size()-1]->setDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
    list[list.size() - 1]->updateCur();
    list[list.size() - 1]->setNull();
    update();
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
    switch (animationState) {
        case AnimationState::INSERTING:
            
            break;
        case AnimationState::DELETING:

            break;
        case AnimationState::SEARCHING:

            break;
        case AnimationState::UPDATING:

            break;
        case AnimationState::IDLE:
        default:
            break;
    }
    cur->update();
    if(list.empty()){
        head->setTarget({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    head->update();
    if (!list.empty()) {
        head->setTarget(list[0]->getStartPos());
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTarget(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTarget({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::draw(){
    cur->draw();
    if(isCreated)
        head->draw();
    for (auto node : list) {
        if (!node) continue;
        node->drawCur();
    }
}