#include "GUI/Panel.h"

Panel::Panel(){
    this->dataTitle = {dataTitlePosition.x-dataTitleSize.x/2.0f,dataTitlePosition.y-dataTitleSize.y/2.0f,dataTitleSize.x,dataTitleSize.y};

    this->Back.setSize(backSize);
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});
    this->Back.setColor(panelNormal,panelHovered,panelPressed);
    this->Back.setRectangle();

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400,350};
}

bool Panel::isBackPressed(){ 
    return Back.isPressed();
}

void Panel::updatePanel(){
    updateController();
}

void Panel::drawPanel(){
    drawController();
    DrawRectangleRounded(dataTitle,100,0,dataTitleColor);
    DrawRectangleRounded(panelHolder,0,0,panelNormal);
}