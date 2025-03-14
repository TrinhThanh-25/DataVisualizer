#include "ShortestPath/STArrow.h"

STArrow::STArrow(Vector2 pos): Arrow(pos){
    this->to=0;
    this->weight=0;
}

void STArrow::setTarget(Vector2 targetPos){
    this->targetDestination=targetPos;
}

void STArrow::update(){
    destination.x += ((targetDestination.x-destination.x));
    destination.y += ((targetDestination.y-destination.y));
}

void STArrow::draw(bool isWeighted, bool isDirected){
    DrawLineEx(this->position,this->destination,2,BLACK);
    if(isWeighted)
        DrawText(std::to_string(this->weight).c_str(),(this->position.x+this->destination.x)/2,(this->position.y+this->destination.y)/2,10,BLACK);
    if(isDirected){
        drawArrow(this->position,this->destination);
    }
}

void STArrow::setWeight(int weight){
    this->weight=weight;
}

int STArrow::getWeight(){
    return this->weight;
}

void STArrow::setTo(int to){
    this->to=to;
}

int STArrow::getTo(){
    return this->to;
}

void STArrow::setFrom(int from){
    this->from=from;
}

int STArrow::getFrom(){
    return this->from;
}