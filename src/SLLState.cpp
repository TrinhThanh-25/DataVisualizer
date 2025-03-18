#include "SLL/SLLState.h"

SLLState::SLLState(): createBox(120,700,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor), indexBox(120,700,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor), valueBox(120,825,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor){
    this->Random.setText("Random",SLLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",SLLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Front.setText("Front",SLLButtonFontSize);
    this->Front.setSize({120, 30});
    this->Front.setPosition({180,760});
    this->Front.setColor(panelNormal,panelHovered,panelPressed);
    this->Front.setRectangle();

    this->End.setText("Back",SLLButtonFontSize);
    this->End.setSize({120, 30});
    this->End.setPosition({320,760});
    this->End.setColor(panelNormal,panelHovered,panelPressed);
    this->End.setRectangle();

    this->Apply.setText("Apply",SLLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    createBox.setNameBox("Input Elements");
    indexBox.setNameBox("Index");
    valueBox.setNameBox("Value");
}

void SLLState::update(){
    SLL.update();
    panel.update();
    if(panel.isCreateUsed()){
        valueBox.setPosition({120,825});
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Front.deActive();
        End.deActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        if(panel.isAddUsed())
            valueBox.setPosition({120,825});
        else
            valueBox.setPosition({120,700});
        Front.setActive();
        End.setActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isUpdateUsed()){
        valueBox.setPosition({120,825});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isSearchUsed()){
        valueBox.setPosition({120,700});
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
    DrawText("Singly Linked List",GetScreenWidth()/2.0f-MeasureText("Singly Linked List",dataTitleFontSize)/2.0f,40-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    SLLCode.draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        if(!panel.isUpdateUsed()){
            this->Front.drawRectangleRounded(100);
            this->Front.drawText(panelSubButtonTextColor);
            this->End.drawRectangleRounded(100);
            this->End.drawText(panelSubButtonTextColor);
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

bool SLLState::isBackPressed(){
    return panel.isBackPressed();
}