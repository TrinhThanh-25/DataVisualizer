#include "AVL/AVLState.h"

AVLState::AVLState(): createBox(120,700,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,AVLBoxColor, AVLBoxTextColor), valueBox(120,700,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,AVLBoxColor, AVLBoxTextColor){
    this->Random.setText("Random",AVLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",AVLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",AVLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    createBox.setNameBox("Input Elements");
    valueBox.setNameBox("Value");
}

void AVLState::update(){
    if (panel.isPlayPressed()) {
        if(currentStep==stateList.size()-1){
            restart();
        }
        else if(currentStep==0){
            play();
        }
        else if(isPlaying&&!isPaused){
            pause();
        }
        else if(isPlaying&&isPaused){
            resume();
        }
    }
    else if (panel.isNextPressed()) {
        nextStep();
    }
    else if (panel.isPrevPressed()) {
        prevStep();
    }
    else if (panel.isEndPressed()) {
        moveEnd();
    }
    else if (panel.isStartPressed()) {
        moveStart();
    }

    AVLTree.update();
    panel.update();
    code.update();

    switch (animationState) {
        case AVLAnimationMode::INSERT:
            if (!isStateSaved) {
                saveInsertState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateInsert(std::stoi(valueText));
            break;
        case AVLAnimationMode::REMOVE:
            if (!isStateSaved) {
                saveRemoveState(std::stoi(valueText));
                isStateSaved = true; 
            }
            animateRemove(std::stoi(valueText));
            break;
        case AVLAnimationMode::SEARCH:
            if (!isStateSaved) {
                saveSearchState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateSearch(std::stoi(valueText));
            break;
        case AVLAnimationMode::IDLE:
            break;
        default:
            break;
    }

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
        //createBox.setText(loadFileContent());
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        valueText=valueBox.GetText();
        createText=createBox.GetText();
        resetBox();
        if(panel.isCreateUsed()&&createText!=""){
            AVLTree.createTree(createText);
        }
        else if(panel.isAddUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::INSERT;
            //AVLTree.insertNode(std::stoi(valueText));
        }
        else if(panel.isRemoveUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::REMOVE;
            //AVLTree.removeNode(std::stoi(valueText));
        }
        else if(panel.isSearchUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::SEARCH;
            //AVLTree.searchNode(std::stoi(valueText));
        } 
    }
    else if(panel.isBackPressed()){
        AVLTree.clearTree();
        resetBox();
    }
    else if(panel.isAnyButtonPressed()){
        AVLTree.resetHighlight();
        resetBox();
    }
    if(panel.isCreateUsed()){
        createBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Update();
    }
}

void AVLState::draw(){
    code.draw();
    AVLTree.draw();
    panel.draw();
    DrawText("AVL Tree",GetScreenWidth()/2.0f-MeasureText("AVL Tree",dataTitleFontSize)/2.0f,dataTitlePosition.y-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    AVLCode.draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Draw();
    }
}

void AVLState::saveInsertState(int value){}
void AVLState::saveRemoveState(int value){}
void AVLState::saveSearchState(int value){}

void AVLState::animateInsert(int value){}
void AVLState::animateRemove(int value){}
void AVLState::animateSearch(int value){}

void AVLState::resetBox(){
    createBox.resetBox();
    valueBox.resetBox();
}

std::string AVLState::getRandomInput(){
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

bool AVLState::isBackPressed(){
    return panel.isBackPressed();
}

void AVLState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void AVLState::pause() {
    isPaused = true;  
}

void AVLState::resume() {
    isPaused = false;
}

void AVLState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void AVLState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void AVLState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void AVLState::moveEnd(){
    isPlaying=false;
    isPaused=true;
    currentStep=stateList.size()-1;
    applyState();
}

void AVLState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void AVLState::saveState(){
    AVL* currentState = AVLTree.clone();
    AVLAnimationMode currentMode = this->animationState;
    stateList.push_back(new AnimationStep{currentState, currentMode});
}

void AVLState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    AVLTree.clear();
    AVLTree = *stateList[currentStep]->AVLTree->clone();
    animationState=stateList[currentStep]->animationState;
}
void AVLState::clearState(){
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}