#include "GUI/Panel.h"

Panel::Panel(){
    this->dataTitle = {600,15,400,50};

    this->Back.setSize({50,50});
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});
    this->Back.setColor(panelNormal,panelHovered,panelPressed);
    this->Back.setRectangle();

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400,350};
}

bool Panel::isBackPressed(){ 
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {dataTitle.y,dataTitle.y,Back.getSize().x,Back.getSize().y});
}