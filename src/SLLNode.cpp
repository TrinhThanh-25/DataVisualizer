#include "SLL/SLLNode.h"

SLLNode::SLLNode() : Pointer(nullptr) {}

SLLNode::~SLLNode(){
    delete Pointer;
}

void SLLNode::setNull(){
    if (Pointer) {
        Pointer->setNull();
    }
}

void SLLNode::setValue(int value){
    this->value=value;
}

void SLLNode::setPosition(Vector2 position){
    this->position = position;
    this->node = {position.x, position.y, SLLNodeSize.x, SLLNodeSize.y};

    if (Pointer) delete Pointer;
    Pointer = new SLLArrow(getEndPos());
}

Vector2 SLLNode::getStartPos(){
    return {position.x, position.y+node.height/2.0f};
}

Vector2 SLLNode::getEndPos(){
    return {position.x+node.width,position.y+node.height/2.0f};
}

Vector2 SLLNode::getPosition(){
    return position;
}


int SLLNode::getValue(){
    return value;
}

void SLLNode::updateCur(Vector2 targetPos){
    if (Pointer) {
        Pointer->setTarget(targetPos);
        Pointer->update();
    }
}

void SLLNode::drawCur(){
    DrawRectangleRounded(node, 50, 0, LIGHTGRAY);
    DrawText(std::to_string(this->value).c_str(),position.x+SLLNodeSize.x/2-MeasureText(std::to_string(this->value).c_str(),24)/2.0f,position.y+SLLNodeSize.y/2-12,24,BLACK);
    if (Pointer) {
        Pointer->draw();
    }
}