#include <GUI/Panel.h>

Panel::Panel(){
    this->dataTitle = {dataTitlePosition.x-dataTitleSize.x/2.0f,dataTitlePosition.y-dataTitleSize.y/2.0f,dataTitleSize.x,dataTitleSize.y};

    this->Back.setSize(backSize);
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),panelButtonSize.x+(panelButtonSize.y-panelButtonFontSize),250+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f)};
    this->subPanelHolder = {panelHolder.width,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400-panelHolder.width,250+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f)};
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
    if(isUsing){
        DrawRectangleRounded(subPanelHolder, 0, 0, buttonNormal); 
        DrawRectangleLinesEx(subPanelHolder,3, outlineButtonColor);
    }
    DrawRectangleRounded(dataTitle,100,0,dataTitleColor);
    DrawRectangleRoundedLinesEx(dataTitle,100,0,3,dataTitleTextColor);
    DrawRectangleRounded(panelHolder,0,0,buttonNormal);
    DrawRectangleLinesEx(panelHolder,3,outlineButtonColor);
}

void Panel::reset(){
    if(!isUsing) return;
    isUsing->deSelected();
    isUsing=nullptr;
}