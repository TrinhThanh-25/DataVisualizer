#include "AVL/AVLNode.h"

AVLNode::AVLNode() : parent(nullptr), left(nullptr), right(nullptr), leftPointer(nullptr), rightPointer(nullptr) {}

AVLNode::~AVLNode(){
    delete left;
    delete right;
    delete leftPointer;
    delete rightPointer;
}

void AVLNode::setValue(int value){
    this->value=value;
}

void AVLNode::setPosition(Vector2 position){
    this->position=position;
    this->node = {position.x-AVLNodeSize.x/2.0f,position.y-AVLNodeSize.y/2.0f, AVLNodeSize.x, AVLNodeSize.y};
    if(leftPointer) delete leftPointer;
    leftPointer = new AVLArrow({position.x,position.y});
    if(rightPointer) delete rightPointer;
    rightPointer = new AVLArrow({position.x,position.y});
}

void AVLNode::setHeight(int value){
    height=value;
}

void AVLNode::setDepth(int value){
    depth=value;
}

void AVLNode::setHighlight(){
    isHighlight=true;
}

void AVLNode::deHighlight(){
    isHighlight=false;
}

Vector2 AVLNode::getOrigin(){
    return position;
}

int AVLNode::getValue(){
    return value;
}

int AVLNode::getDepth(){
    return depth;
}

int AVLNode::getHeight(){
    return height;
}

bool AVLNode::isLeaf(){
    return (!left&&!right);
}

void AVLNode::updateHeight(){
    if(!left&&!right) height=1;
    else if(!left) height=1+right->getHeight();
    else if(!right) height=1+left->getHeight();
    else height=1+std::max(left->getHeight(),right->getHeight());
}

void AVLNode::updateCur(){
    if(left&&leftPointer){
        leftPointer->setTarget(left->getOrigin());
        leftPointer->update();
    }
    if(right&&rightPointer){
        rightPointer->setTarget(right->getOrigin());
        rightPointer->update();
    }
}

void AVLNode::drawCur(){
    if(left&&leftPointer){
        leftPointer->draw();
    }
    if(right&&rightPointer){
        rightPointer->draw();
    }
    if(!isHighlight)
        DrawRectangleRounded(node,100,0,LIGHTGRAY);
    else  
        DrawRectangleRounded(node,100,0,RED);
    DrawText(std::to_string(this->value).c_str(),position.x-MeasureText(std::to_string(this->value).c_str(),24)/2.0f,position.y-12,24,BLACK);
}