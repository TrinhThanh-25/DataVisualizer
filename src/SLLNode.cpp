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

void SLLNode::setTarget(Vector2 target){
    if(Pointer)
    Pointer->setTarget(target);
}

void SLLNode::setTargetPosition(Vector2 targetPos){
    this->targetPosition=targetPos;
}

void SLLNode::setDestination(Vector2 targetPos){
    Pointer->setDestination(targetPos);
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

void SLLNode::updateNode(){
    if (position.x == targetPosition.x&&position.y == targetPosition.y) return;
    float deltaTime=GetFrameTime();
    float disX=targetPosition.x-position.x, disY=targetPosition.y-position.y;
    float dis=sqrt(disX*disX+disY*disY);
    float deltaX=disX/dis*speed*deltaTime;
    float deltaY=disY/dis*speed*deltaTime;
    if(deltaX>=disX&&deltaY>=disY){
        position=targetPosition;
    }
    else{
        position.x+=deltaX;
        position.y+=deltaY;
    }
}

void SLLNode::updateCur(){
    updateNode();
    node={position.x, position.y, SLLNodeSize.x, SLLNodeSize.y};
    if (Pointer) {
        Pointer->setPosition(getEndPos());
        Pointer->update();
    }
}

void SLLNode::drawCur(){
    DrawRectangleRounded(node, 50, 100, LIGHTGRAY);
    DrawText(std::to_string(this->value).c_str(),position.x+SLLNodeSize.x/2.0f-MeasureText(std::to_string(this->value).c_str(),SLLNodeFontSize)/2.0f,position.y+SLLNodeSize.y/2.0f-SLLNodeFontSize/2.0f,SLLNodeFontSize,SLLNodeTextColor);
    if (Pointer) {
        Pointer->draw();
    }
}