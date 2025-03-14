#include "GUI/Arrow.h"

Arrow::Arrow(Vector2 pos)
    : position(pos), destination(pos), targetDestination(pos) {}

void Arrow::setTarget(Vector2 targetPos){
    targetDestination=targetPos;
}

void Arrow::setPosition(Vector2 position){
    this->position=position;
}

Vector2 Arrow::getPosition(){
    return position;
}

void Arrow::update(){
    destination.x += ((targetDestination.x-destination.x));
    destination.y += ((targetDestination.y-destination.y));
}

void Arrow::draw(){
    drawArrow(position, destination);
}

void Arrow::drawArrow(Vector2 position, Vector2 destination){
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