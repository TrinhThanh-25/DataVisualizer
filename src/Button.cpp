#include "GUI/Button.h"

Button::Button(){}

void Button::setTexture(const char* path){
    this->texture = LoadTexture(path);
}

void Button::setPosition(int posX, int posY){
    this->position.x = posX;
    this->position.y = posY;
}

void Button::setSize(int width, int height){
    this->size.x=width;
    this->size.y=height;
}

void Button::setText(const char* text, int fontSize){
    this->text = text;
    this->fontSize=fontSize;
}

void Button::setRectangle(){
    rectangle = {position.x - size.x/2,position.y-(size.y/2-fontSize/2),size.x,size.y};
}

void Button::update(){
    if(this->isSeclected){
        color=RED;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=RED;
        }else{
            color=YELLOW;
        }
    }
    else{
        color=BLUE;
    }
}

void Button::drawRectangle(int width, int height){
    DrawRectangle(this->position.x, this->position.y, width, height, this->color);
}

void Button::drawRectangleRounded(int roundness){
    DrawRectangleRounded(this->rectangle, roundness, 0, this->color);
}

void Button::drawRectangleRoundedLinesEx(int roundness, int segments, int lineThick, Color color){
    DrawRectangleRoundedLinesEx(this->rectangle, roundness, segments, lineThick,color);
}

void Button::drawTexture(Vector2 position){
    DrawTexture(this->texture, position.x, position.y, WHITE);
}

void Button::drawText(Color color){
    DrawText(this->text, position.x - MeasureText(text,fontSize)/2 ,position.y, this->fontSize, color);
}

Vector2 Button::getSize(){
    return this->size;
}

Vector2 Button::getPosition(){
    return this->position;
}

int Button::getfontSize(){
    return this->fontSize;
}

bool Button::isPressed(){
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

bool Button::isHovered(){
    return CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

void Button::Selected(){
    this->isSeclected = true;
}

void Button::deSelected(){
    this->isSeclected = false;
}