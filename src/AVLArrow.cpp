#include "AVL/AVLArrow.h"

AVLArrow::AVLArrow(Vector2 pos): Arrow(pos){}

void AVLArrow::setTarget(Vector2 targetPos){
    this->targetDestination=targetPos;
}

void AVLArrow::update(){
    this->destination.x += ((this->targetDestination.x-this->destination.x));
    this->destination.y += ((this->targetDestination.y-this->destination.y));
}

void AVLArrow::draw(){
    DrawLineEx(this->position,this->destination,2,color);
}