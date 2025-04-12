#include <SLL/SLLPanel.h>

SLLPanel::SLLPanel(){
    this->Create.setText("Create",panelButtonFontSize);
    this->Create.setSize(panelButtonSize);
    this->Create.setPosition({Create.getSize().x/2.0f+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f), 650+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f)});

    this->Add.setText("Add",panelButtonFontSize);
    this->Add.setSize(panelButtonSize);
    this->Add.setPosition({Add.getSize().x/2.0f+(Add.getSize().y/2.0f-Add.getfontSize()/2.0f), 700+(Add.getSize().y/2.0f-Add.getfontSize()/2.0f)});

    this->Remove.setText("Remove",panelButtonFontSize);
    this->Remove.setSize(panelButtonSize);
    this->Remove.setPosition({Remove.getSize().x/2.0f+(Remove.getSize().y/2.0f-Remove.getfontSize()/2.0f), 750+(Remove.getSize().y/2.0f-Remove.getfontSize()/2.0f)});

    this->Search.setText("Search",panelButtonFontSize);
    this->Search.setSize(panelButtonSize);
    this->Search.setPosition({Search.getSize().x/2.0f+(Search.getSize().y/2.0f-Search.getfontSize()/2.0f), 800+(Search.getSize().y/2.0f-Search.getfontSize()/2.0f)});

    this->Update.setText("Update",panelButtonFontSize);
    this->Update.setSize(panelButtonSize);
    this->Update.setPosition({Update.getSize().x/2.0f+(Update.getSize().y/2.0f-Update.getfontSize()/2.0f), 850+(Update.getSize().y/2.0f-Update.getfontSize()/2.0f)});
}

bool SLLPanel::isAnyButtonPressed(){
    return Create.isPressed()||Add.isPressed()||Remove.isPressed()||Update.isPressed()||Search.isPressed();
}

void SLLPanel::draw(){
    drawPanel();
    this->Back.drawRectangleRounded(100);
    this->Create.drawRectangleRounded(100);
    this->Create.drawText();
    this->Add.drawRectangleRounded(100);
    this->Add.drawText();
    this->Remove.drawRectangleRounded(100);
    this->Remove.drawText();
    this->Update.drawRectangleRounded(100);
    this->Update.drawText();
    this->Search.drawRectangleRounded(100);
    this->Search.drawText();
    this->Back.drawOutlineRounded(100,0,3);
    this->Create.drawOutlineRounded(100,0,3);
    this->Add.drawOutlineRounded(100,0,3);
    this->Remove.drawOutlineRounded(100,0,3);
    this->Update.drawOutlineRounded(100,0,3);
    this->Search.drawOutlineRounded(100,0,3);
}

void SLLPanel::update(){
    updatePanel();
    if(this->Create.isPressed()){
        if(isUsing&&isUsing==&Create) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Create.Selected();
            if(isUsing&&isUsing!=&Create) this->isUsing->deSelected();
            this->isUsing = &this->Create;
        }
    }
    else if(this->Add.isPressed()){
        if(isUsing&&isUsing==&Add) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Add.Selected();
            if(isUsing&&isUsing!=&Add) this->isUsing->deSelected();
            this->isUsing = &this->Add;
        }
    }
    else if(this->Remove.isPressed()){
        if(isUsing&&isUsing==&Remove) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Remove.Selected();
            if(isUsing&&isUsing!=&Remove) this->isUsing->deSelected();
            this->isUsing = &this->Remove;
        }
    }
    else if(this->Update.isPressed()){
        if(isUsing&&isUsing==&Update) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Update.Selected();
            if(isUsing&&isUsing!=&Update) this->isUsing->deSelected();
            this->isUsing = &this->Update;
        }
    }
    else if(this->Search.isPressed()){
        if(isUsing&&isUsing==&Search) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Search.Selected();
            if(isUsing&&isUsing!=&Search) this->isUsing->deSelected();
            this->isUsing = &this->Search;
        }
    }
    this->Back.update();
    this->Create.update();
    this->Add.update(); 
    this->Remove.update();
    this->Update.update();
    this->Search.update();
}

bool SLLPanel::isCreateUsed(){
    return (isUsing == &Create);
}

bool SLLPanel::isAddUsed(){
    return (isUsing == &Add);
}

bool SLLPanel::isRemoveUsed(){
    return (isUsing == &Remove);
}

bool SLLPanel::isSearchUsed(){
    return (isUsing == &Search);
}

bool SLLPanel::isUpdateUsed(){
    return (isUsing==&Update);
}