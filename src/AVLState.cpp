#include "AVL/AVLState.h"

AVLState::AVLState(): createBox(120,650,260,40,20,LIGHTGRAY,BLACK), valueBox(120,650,260,40,20,LIGHTGRAY,BLACK){
    this->Random.setText("Random",15);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,710});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",15);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,710});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",15);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,750});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();
}

void AVLState::update(){
    AVL.update();
    panel.update();
    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        createBox.setText(getRandomInput());
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        if(panel.isCreateUsed()&&createBox.GetText()!=""){
            AVL.createTree(createBox.GetText());
        }
        else if(panel.isAddUsed()&&valueBox.GetText()!=""){
            AVL.insertNode(std::stoi(valueBox.GetText()));
        }
        else if(panel.isRemoveUsed()&&valueBox.GetText()!=""){
            AVL.removeNode(std::stoi(valueBox.GetText()));
        }
        else if(panel.isSearchUsed()&&valueBox.GetText()!=""){
            AVL.searchNode(std::stoi(valueBox.GetText()));
        } 
        resetBox();
    }
    else if(panel.isBackPressed()){
        AVL.clearTree();
        resetBox();
    }
    else if(panel.isAnyButtonPressed()){
        resetBox();
    }
    if(panel.isCreateUsed()){
        createBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(!panel.isUpdateUsed()){
        valueBox.Update();
    }
}

void AVLState::draw(){
    AVL.draw();
    panel.draw();
    DrawText("AVL Tree",800-MeasureText("AVL Tree",24)/2.0f,40-12,24, BLACK);
    AVLCode.draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(BLACK);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(BLACK);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(BLACK);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Draw();
    }
}

void AVLState::resetBox(){
    createBox.resetBox();
    valueBox.resetBox();
}

std::string AVLState::getRandomInput(){
    srand(time(NULL));
    int numElement=rand()%30;
    std::string elements="";
    for (int i=0;i<=numElement;i++){
        if(i==numElement){
            elements+=std::to_string(rand()%100);
            continue;
        }
        elements+= std::to_string(rand()%100) +",";
    }
    return elements;
}