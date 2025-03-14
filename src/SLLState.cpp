#include "SLL/SLLState.h"

SLLState::SLLState(): createBox(120,650,260,40,20,LIGHTGRAY,BLACK), indexBox(120,650,260,40,20,LIGHTGRAY,BLACK), valueBox(120,775,260,40,20,LIGHTGRAY,BLACK){
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

    this->Front.setText("Front",15);
    this->Front.setSize({120, 30});
    this->Front.setPosition({180,710});
    this->Front.setColor(panelNormal,panelHovered,panelPressed);
    this->Front.setRectangle();

    this->End.setText("Back",15);
    this->End.setSize({120, 30});
    this->End.setPosition({320,710});
    this->End.setColor(panelNormal,panelHovered,panelPressed);
    this->End.setRectangle();

    this->Apply.setText("Apply",15);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,750});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();
}

void SLLState::update(){
    SLL.update();
    panel.update();
    if(panel.isCreateUsed()){
        valueBox.setPosition({120,775});
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Front.deActive();
        End.deActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        if(panel.isAddUsed())
            valueBox.setPosition({120,775});
        Front.setActive();
        End.setActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isUpdateUsed()){
        valueBox.setPosition({120,775});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isSearchUsed()){
        valueBox.setPosition({120,650});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        createBox.setText(getRandomInput());
    }
    else if(Front.isPressed()){
        indexBox.setText("0");
    }
    else if(End.isPressed()){
        if(panel.isAddUsed())
            indexBox.setText(std::to_string(SLL.getListSize()));
        else if(panel.isRemoveUsed()){
            indexBox.setText(std::to_string(SLL.getListSize()-1));
        }
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        if(panel.isCreateUsed()&&createBox.GetText()!=""){
            SLL.createList(createBox.GetText());
        }
        else if(panel.isAddUsed()&&indexBox.GetText()!=""&&valueBox.GetText()!=""){
            SLL.insertNode(std::stoi(indexBox.GetText()),std::stoi(valueBox.GetText()));
        }
        else if(panel.isRemoveUsed()&&indexBox.GetText()!=""){
            SLL.removeNode(std::stoi(indexBox.GetText()));
        }
        else if(panel.isUpdateUsed()&&valueBox.GetText()!=""){
            SLL.updateNode(std::stoi(indexBox.GetText()),std::stoi(valueBox.GetText()));
        }
        else if(panel.isSearchUsed()&&valueBox.GetText()!=""){
            SLL.searchNode(std::stoi(valueBox.GetText()));
        } 
        resetBox();
    }
    else if(panel.isBackPressed()){
        SLL.clearList();
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
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        this->Front.update();
        this->End.update();
        indexBox.Update();
        if(!panel.isRemoveUsed())
            valueBox.Update();
    }
    else if(panel.isSearchUsed()){
        valueBox.Update();
    }
}

void SLLState::draw(){
    SLL.draw();
    panel.draw();
    DrawText("Singly Linked List",800-MeasureText("Singly Linked List",24)/2.0f,40-12,24, BLACK);
    SLLCode.draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(BLACK);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(BLACK);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(BLACK);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        if(!panel.isUpdateUsed()){
            this->Front.drawRectangleRounded(100);
            this->Front.drawText(BLACK);
            this->End.drawRectangleRounded(100);
            this->End.drawText(BLACK);
        }
        indexBox.Draw();
        if(!panel.isRemoveUsed())
            valueBox.Draw();
    }
    else if(panel.isSearchUsed()){
        valueBox.Draw();
    }
}

void SLLState::resetBox(){
    createBox.resetBox();
    indexBox.resetBox();
    valueBox.resetBox();
}

std::string SLLState::getRandomInput(){
    srand(time(NULL));
    int numElement=rand()%10;
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