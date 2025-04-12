#include <GUI/Button.h>

Button::Button(){}

void Button::setTexture(const char* path){
    this->texture = LoadTexture(path);
}

void Button::setPosition(Vector2 position){
    this->position=position;
    this->rectangle = {position.x - size.x/2,position.y-(size.y/2-fontSize/2),size.x,size.y};
}

void Button::setSize(Vector2 size){
    this->size=size;
    this->rectangle = {position.x - size.x/2,position.y-(size.y/2-fontSize/2),size.x,size.y};
}

void Button::setText(const char* text, int fontSize){
    this->text = text;
    this->fontSize=fontSize;
}

void Button::update(){
    if(this->selected){
        color=buttonPressed;
        outlineColor=outlineButtonPressedColor;
        textColor=textButtonPressed;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=buttonPressed;
            outlineColor=outlineButtonPressedColor;
            textColor=textButtonPressed;
        }else{
            color=buttonHovered;
            outlineColor=outlineButtonHoveredColor;
            textColor=textButtonHovered;
        }
    }
    else{
        color=buttonNormal;
        outlineColor=outlineButtonColor;
        textColor=textButtonNormal;
    }
}

void Button::update(ColorTheme theme){
    color=theme.buttonNormal;
    outlineColor=theme.outlineButtonColor;
    textColor=theme.textButtonNormal;
    if(this->selected){
        color=theme.buttonPressed;
        outlineColor=theme.outlineButtonPressedColor;
        textColor=theme.textButtonPressed;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=theme.buttonPressed;
            outlineColor=theme.outlineButtonPressedColor;
            textColor=theme.textButtonPressed;
        }else{
            color=theme.buttonHovered;
            outlineColor=theme.outlineButtonHoveredColor;
            textColor=theme.textButtonHovered;
        }
    }
}

void Button::drawRectangle(Vector2 recSize){
    DrawRectangle(this->position.x, this->position.y, recSize.x, recSize.y, this->color);
}

void Button::drawRectangleRounded(int roundness){
    DrawRectangleRounded(this->rectangle, roundness, 100, this->color);
}

void Button::drawTexture(Vector2 position){
    DrawTexture(this->texture, position.x, position.y, WHITE);
}

void Button::drawOutlineRounded(int roundness, int segments, int lineThick){
    DrawRectangleRoundedLinesEx(this->rectangle, roundness, segments, lineThick, this->outlineColor);
}

void Button::drawText(){
    DrawText(this->text, position.x - MeasureText(text, fontSize)/2 ,position.y, this->fontSize, textColor);
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
    return isActive&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

bool Button::isHovered(){
    return isActive&&CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

bool Button::isSelected(){
    return this->selected;
}

void Button::Selected(){
    this->selected = true;
}

void Button::deSelected(){
    this->selected = false;
}

void Button::setActive(){
    isActive=true;
}

void Button::deActive(){
    isActive=false;
}