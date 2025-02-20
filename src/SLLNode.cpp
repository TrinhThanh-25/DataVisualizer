#include "SLL/SLLNode.h"

SLLNode::SLLNode(){}

void SLLNode::setValue(int value){
    this->value=value;
    this->text = std::to_string(value);
}

void SLLNode::setPosition(float posX, float posY){
    this->position={posX, posY};
    this->node={position.x, position.y, 40.0f, 40.0f};
    this->endPos={position.x+40.0f,position.y+20.0f};
    this->startPos={position.x, position.y+20.0f};
}

Vector2 SLLNode::getStartPos(){
    return startPos;
}

Vector2 SLLNode::getEndPos(){
    return endPos;
}

void SLLNode::drawCur(){
    DrawRectangleRounded(node,50,0,LIGHTGRAY);
}





