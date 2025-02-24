#include "GUI/Panel.h"

Panel::Panel(){
    this->dataTitle = {800-200,30-15,400,50};

    this->Back.setSize({50,50});
    this->Back.setPosition({dataTitle.y+dataTitle.height/2,dataTitle.y+dataTitle.height/2});
    this->Back.setColor(panelNormal,panelHovered,panelPressed);
    this->Back.setRectangle();

    this->Create.setText("Create",15);
    this->Create.setSize({80, 40});
    this->Create.setPosition({Create.getSize().x/2+(Create.getSize().y/2-Create.getfontSize()/2), 600+(Create.getSize().y/2-Create.getfontSize()/2)});
    this->Create.setColor(panelNormal,panelHovered,panelPressed);
    this->Create.setRectangle();

    this->Add.setText("Add",15);
    this->Add.setSize({80, 40});
    this->Add.setPosition({Add.getSize().x/2+(Add.getSize().y/2-Add.getfontSize()/2), 650+(Add.getSize().y/2-Add.getfontSize()/2)});
    this->Add.setColor(panelNormal,panelHovered,panelPressed);
    this->Add.setRectangle();

    this->Remove.setText("Remove",15);
    this->Remove.setSize({80, 40});
    this->Remove.setPosition({Remove.getSize().x/2+(Remove.getSize().y/2-Remove.getfontSize()/2), 700+(Remove.getSize().y/2-Remove.getfontSize()/2)});
    this->Remove.setColor(panelNormal,panelHovered,panelPressed);
    this->Remove.setRectangle();

    this->Update.setText("Update",15);
    this->Update.setSize({80, 40});
    this->Update.setPosition({Update.getSize().x/2+(Update.getSize().y/2-Update.getfontSize()/2), 750+(Update.getSize().y/2-Update.getfontSize()/2)});
    this->Update.setColor(panelNormal,panelHovered,panelPressed);
    this->Update.setRectangle();

    this->Search.setText("Search",15);
    this->Search.setSize({80, 40});
    this->Search.setPosition({Search.getSize().x/2+(Search.getSize().y/2-Search.getfontSize()/2), 800+(Search.getSize().y/2-Search.getfontSize()/2)});
    this->Search.setColor(panelNormal,panelHovered,panelPressed);
    this->Search.setRectangle();

    this->Clear.setText("Clear",15);
    this->Clear.setSize({80, 40});
    this->Clear.setPosition({Clear.getSize().x/2+(Clear.getSize().y/2-Clear.getfontSize()/2), 850+(Clear.getSize().y/2-Clear.getfontSize()/2)});
    this->Clear.setColor(panelNormal,panelHovered,panelPressed);
    this->Clear.setRectangle();

    this->panelHolder = {0,600-(Clear.getSize().y/2-Clear.getfontSize()/2),400,350};
}

bool Panel::isBackPressed(){
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {15,15,50,50});
}

void Panel::draw(){
    DrawRectangle(1200,600-(Clear.getSize().y/2-Clear.getfontSize()/2),400,350,panelNormal);
    DrawRectangle(550,800,500,100,panelNormal);

    
    DrawRectangleRounded(dataTitle,100,0,titleColor);
    DrawRectangleRounded(panelHolder,0,0,panelNormal);
    this->Back.drawRectangleRounded(100);
    this->Create.drawRectangleRounded(100);
    this->Create.drawText(BLACK);
    this->Add.drawRectangleRounded(100);
    this->Add.drawText(BLACK);
    this->Remove.drawRectangleRounded(100);
    this->Remove.drawText(BLACK);
    this->Update.drawRectangleRounded(100);
    this->Update.drawText(BLACK);
    this->Search.drawRectangleRounded(100);
    this->Search.drawText(BLACK);
    this->Clear.drawRectangleRounded(100);
    this->Clear.drawText(BLACK);
}

void Panel::update(){
    if(this->Create.isPressed()){
        this->Create.Selected();
        if(isUsing&&isUsing!=&Create) this->isUsing->deSelected();
        this->isUsing = &this->Create;
    }
    else if(this->Add.isPressed()){
        this->Add.Selected();
        if(isUsing&&isUsing!=&Add) this->isUsing->deSelected();
        this->isUsing = &this->Add;
    }
    else if(this->Remove.isPressed()){
        this->Remove.Selected();
        if(isUsing&&isUsing!=&Remove) this->isUsing->deSelected();
        this->isUsing = &this->Remove;
    }
    else if(this->Update.isPressed()){
        this->Update.Selected();
        if(isUsing&&isUsing!=&Update) this->isUsing->deSelected();
        this->isUsing = &this->Update;
    }
    else if(this->Search.isPressed()){
        this->Search.Selected();
        if(isUsing&&isUsing!=&Search) this->isUsing->deSelected();
        this->isUsing = &this->Search;
    }
    else if(this->Clear.isPressed()){
        this->Clear.Selected();
        if(isUsing&&isUsing!=&Clear) this->isUsing->deSelected();
        this->isUsing = &this->Clear;
    }
    if(isBackPressed()){
        if(isUsing) this->isUsing->deSelected();
    }
    this->Back.update();
    this->Create.update();
    this->Add.update(); 
    this->Remove.update();
    this->Update.update();
    this->Search.update();
    this->Clear.update(); 
}

