#include "GUI/Arrow.h"

Arrow::Arrow(Vector2 pos)
    : position(pos), destination(pos), targetDestination(pos) {}

void Arrow::setTarget(Vector2 targetPos){
    targetDestination=targetPos;
}

void Arrow::setDestination(Vector2 destination){
    this->destination=destination;
    targetDestination=destination;
}

void Arrow::setPosition(Vector2 position){
    this->position=position;
}

void Arrow::setTargetPosition(Vector2 targetPos){
    this->targetPosition=targetPos;
}

Vector2 Arrow::getPosition(){
    return position;
}

Vector2 Arrow::getDestination(){
    return destination;
}

void Arrow::setColor(Color color){
    this->color=color;
}

void Arrow::update(){
    if (destination.x == targetDestination.x&&destination.y == targetDestination.y) return;
    float deltaTime=GetFrameTime();
    float disX=targetDestination.x-destination.x, disY=targetDestination.y-destination.y;
    float dis=sqrt(disX*disX+disY*disY);
    float deltaX=disX/dis*speed*deltaTime;
    float deltaY=disY/dis*speed*deltaTime;
    if(deltaX>=disX&&deltaY>=disY){
        destination=targetDestination;
    }
    else{
        destination.x+=deltaX;
        destination.y+=deltaY;
    }
}

void Arrow::draw(){
    drawArrow(position, destination);
}

void Arrow::drawArrow(Vector2 position, Vector2 destination){
    DrawCircle(position.x,position.y,2,color);
    DrawLineEx(position, destination,2,color);

    Vector2 direction = {destination.x-position.x,destination.y-position.y};
    float length=sqrt(direction.x*direction.x+direction.y*direction.y);
    if(length==0) return;

    direction.x /= length;
    direction.y /= length;

    Vector2 tip = destination;
    Vector2 left = {tip.x - direction.x * 10.0f + direction.y * 5.0f,tip.y - direction.y * 10.0f - direction.x * 5.0f};
    Vector2 right = {tip.x - direction.x * 10.0f - direction.y * 5.0f,tip.y - direction.y * 10.0f + direction.x * 5.0f};

    DrawTriangle(tip, left, right, color);
}