#include "SLL/SLLArrow.h"

SLLArrow::SLLArrow(Vector2 pos) : Arrow(pos), isNull(true){}

void SLLArrow::setLabel(const std::string &text){
    label=text;
}

void SLLArrow::setNull(){
    isNull=true;
}

bool SLLArrow::checkNull(){
    return isNull;
}

void SLLArrow::setTarget(Vector2 targetPos){
    targetDestination=targetPos;
    isNull=false;
}

void SLLArrow::draw(){
    drawArrow(position, destination);
    if(isNull){
        DrawText("null", destination.x + 10, destination.y-8, 16, color);
    }
    if (!label.empty()){
        DrawText(label.c_str(), position.x - 40, position.y-8, 16, color);
    }
}