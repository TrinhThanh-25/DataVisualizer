#include "GUI/Panel.h"

Panel::Panel(){
    this->Create.setText("Create",20);
    this->Create.setSize(100, 50);
    this->Create.setPosition(50, 600);
    this->Create.setRectangle();

    this->Add.setText("Add",20);
    this->Add.setSize(100, 50);
    this->Add.setPosition(50, 650);
    this->Add.setRectangle();

    this->Remove.setText("Remove",20);
    this->Remove.setSize(100, 50);
    this->Remove.setPosition(50, 700);
    this->Remove.setRectangle();

    this->Update.setText("Update",20);
    this->Update.setSize(100, 50);
    this->Update.setPosition(50, 750);
    this->Update.setRectangle();

    this->Search.setText("Search",20);
    this->Search.setSize(100, 50);
    this->Search.setPosition(50, 800);
    this->Search.setRectangle();

    this->Clear.setText("Clear",20);
    this->Clear.setSize(100, 50);
    this->Clear.setPosition(50, 850);
    this->Clear.setRectangle();
}

void Panel::draw(){
    this->Create.drawRectangleRounded(0.7);
    this->Create.drawText(BLACK);
    this->Add.drawRectangleRounded(0.7);
    this->Add.drawText(BLACK);
    this->Remove.drawRectangleRounded(0.7);
    this->Remove.drawText(BLACK);
    this->Update.drawRectangleRounded(0.7);
    this->Update.drawText(BLACK);
    this->Search.drawRectangleRounded(0.7);
    this->Search.drawText(BLACK);
    this->Clear.drawRectangleRounded(0.7);
    this->Clear.drawText(BLACK);
}

void Panel::update(){
    if(this->Create.isPressed()){
        this->Create.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Create;
    }
    else if(this->Add.isPressed()){
        this->Add.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Add;
    }
    else if(this->Remove.isPressed()){
        this->Remove.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Remove;
    }
    else if(this->Update.isPressed()){
        this->Update.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Update;
    }
    else if(this->Search.isPressed()){
        this->Search.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Search;
    }
    else if(this->Clear.isPressed()){
        this->Clear.Selected();
        if(isUsing) this->isUsing->deSelected();
        this->isUsing = &this->Clear;
    }
    this->Create.update();
    this->Add.update(); 
    this->Remove.update();
    this->Update.update();
    this->Search.update();
    this->Clear.update(); 
}

