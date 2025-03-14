#include "SLL/SLLArrow.h"

SLLArrow::SLLArrow(Vector2 pos) : Arrow(pos), isNull(true){}

void SLLArrow::setLabel(const std::string &text){
    label=text;
}

void SLLArrow::setNull(){
    isNull=true;
}

void SLLArrow::setTarget(Vector2 targetPos){
    targetDestination=targetPos;
    isNull=false;
}

void SLLArrow::update(){
    destination.x += ((targetDestination.x-destination.x));
    destination.y += ((targetDestination.y-destination.y));
}

void SLLArrow::draw(){
    drawArrow(position, destination);
    if(isNull){
        DrawText("null", destination.x + 10, destination.y-8, 16, BLACK);
    }
    if (!label.empty()){
        DrawText(label.c_str(), position.x - 40, position.y-8, 16, BLACK);
    }
}