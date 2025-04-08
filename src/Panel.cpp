#include "GUI/Panel.h"

Panel::Panel(){
    this->dataTitle = {dataTitlePosition.x-dataTitleSize.x/2.0f,dataTitlePosition.y-dataTitleSize.y/2.0f,dataTitleSize.x,dataTitleSize.y};

    this->Back.setSize(backSize);
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});
    this->Back.setColor(panelNormal,panelHovered,panelPressed);

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400,350};
    Back.deActive();
}

bool Panel::isBackPressed(){
    bool res=Back.isPressed();
    if(res){
        Back.deActive();
    }
    return res;
}

void Panel::setBackActive(){
    Back.setActive();
}

void Panel::updatePanel(){
    updateController();
}

void Panel::drawPanel(){
    drawController();
    DrawRectangleRounded(dataTitle,100,0,dataTitleColor);
    DrawRectangleRounded(panelHolder,0,0,panelNormal);
}

void Panel::reset(){
    if(!isUsing) return;
    isUsing->deSelected();
    isUsing=nullptr;
}