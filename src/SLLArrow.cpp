#include "SLL/SLLArrow.h"

SLLArrow::SLLArrow(Vector2 pos)
    : position(pos), destination(pos), targetDestination(pos), isNull(true) {}

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

void SLLArrow::setPosition(Vector2 position){
    this->position=position;
}

Vector2 SLLArrow::getPosition(){
    return position;
}

void SLLArrow::update(){
    if(!isNull){
        destination.x += ((targetDestination.x-destination.x)*0.2f);
        destination.y += ((targetDestination.y-destination.y)*0.2f);
    }
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

void SLLArrow::drawArrow(Vector2 position, Vector2 destination){
    DrawCircle(position.x,position.y,2,BLACK);
    DrawLineEx(position, destination,2,BLACK);

    Vector2 direction = {destination.x-position.x,destination.y-position.y};
    float length=sqrt(direction.x*direction.x+direction.y*direction.y);
    if(length==0) return;

    direction.x /= length;
    direction.y /= length;

    Vector2 tip = destination;
    Vector2 left = {tip.x - direction.x * 10.0f + direction.y * 5.0f,tip.y - direction.y * 10.0f - direction.x * 5.0f};
    Vector2 right = {tip.x - direction.x * 10.0f - direction.y * 5.0f,tip.y - direction.y * 10.0f + direction.x * 5.0f};

    DrawTriangle(tip, left, right, BLACK);
}