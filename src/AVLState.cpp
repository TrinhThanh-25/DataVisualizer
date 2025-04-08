//FIX KHI PRESS BACK GIỮA CHỪNG BỊ LỖI

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
        createBox.setText(panel.loadFileContent());
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        AVLTree.resetHighlight();
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
        }
        else if(panel.isRemoveUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::REMOVE;
        }
        else if(panel.isSearchUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::SEARCH;
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

void AVLState::saveInsertState(int value){
    saveState();
    while(true){
        if(!AVLTree.root){
            AVLTree.root = new AVLNode(); 
            AVLTree.root->setValue(value);
            AVLTree.calculateHeight();
            AVLTree.root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
            AVLTree.root->setTargetPosition({(float)GetScreenWidth()/2,AVLPosition.y});
            AVLTree.curNode=AVLTree.root;
            animationState=AVLAnimationMode::IDLE;
            saveState();
            applyState();
            return;
        }
        if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
            AVLTree.curNode->setHighlight();
            AVLTree.animationStep++;
        }
        else if(AVLTree.animationStep==1){
            saveState();
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                if(!AVLTree.curNode->left){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->left;
                }
            }
            else{
                if(!AVLTree.curNode->right){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->right;
                }
            }
            AVLTree.curNode->setHighlight();
        }
        else if(AVLTree.animationStep==2){
            if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode->left=new AVLNode();
                AVLTree.curNode->left->setPosition(AVLTree.curNode->getOrigin());
                AVLTree.curNode->left->setValue(value);
                AVLTree.curNode->left->parent=AVLTree.curNode;
            }
            else{
                AVLTree.curNode->right=new AVLNode();
                AVLTree.curNode->right->setPosition(AVLTree.curNode->getOrigin());
                AVLTree.curNode->right->setValue(value);
                AVLTree.curNode->right->parent=AVLTree.curNode;
            }
            AVLTree.calculateHeight();
            AVLTree.setPosition();
            AVLTree.setArrowDestination();
            AVLTree.animationStep++;
            AVLTree.curNode->deHighlight();
        }
        else if(AVLTree.animationStep==3){
            if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode->left->setHighlight();
                AVLTree.curNode->setDestinationLeft(AVLTree.curNode->left->getOrigin());
                AVLTree.curNode=AVLTree.curNode->left;
            }
            else{
                AVLTree.curNode->right->setHighlight();
                AVLTree.curNode->setDestinationRight(AVLTree.curNode->right->getOrigin());
                AVLTree.curNode=AVLTree.curNode->right;
                
            }
            AVLTree.animationStep++;
        }
        else if(AVLTree.animationStep==4){
            if (AVLTree.curNode) {
                AVLTree.curNode->setHighlight();
                saveState();
                int balanceFactor=getBalanceFactor(AVLTree.curNode);
                if(abs(balanceFactor)>1){
                    if(balanceFactor>1){
                        if(getBalanceFactor(AVLTree.curNode->left)<0) AVLTree.rotateLeftRight(AVLTree.curNode);
                        else AVLTree.rotateRight(AVLTree.curNode);
                    }
                    else if(balanceFactor<-1){
                        if(getBalanceFactor(AVLTree.curNode->right)>0) AVLTree.rotateRightLeft(AVLTree.curNode);
                        else AVLTree.rotateLeft(AVLTree.curNode);
                    }
                    AVLTree.setArrowDestination();
                    AVLTree.animationStep++;
                    saveState();
                }
                else {
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        AVLTree.animationStep=0;
                        saveState();
                        currentStep=0;
                        applyState();
                        return;
                    }
                }
            }
        }
        else if(AVLTree.animationStep==5){
            AVLTree.animationStep++;
            AVLTree.setPosition();
        }
        else if(AVLTree.animationStep==6){
            AVLTree.setArrowDestination();
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::saveRemoveState(int value){
    saveState();
    while(true){
        if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
            AVLTree.curNode->setHighlight();
            AVLTree.animationStep++;
            saveState();
        }   
        else if(AVLTree.animationStep==1){
            if(!AVLTree.curNode){
                AVLTree.animationStep=0;
                animationState=AVLAnimationMode::IDLE;
                AVLTree.curNode=AVLTree.root;
                saveState();
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value==AVLTree.curNode->getValue()){
                AVLTree.animationStep++;
            }
            else if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
            }
            saveState();
        }
        else if(AVLTree.animationStep==2){
            if(AVLTree.curNode->isLeaf()){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = nullptr;
                    else AVLTree.curNode->parent->right = nullptr;
                    AVLTree.curNode=AVLTree.curNode->parent;
                    delete del;
                }
                else {
                    AVLTree.root = nullptr;
                    delete del;
                    AVLTree.curNode=nullptr;
                }
                AVLTree.animationStep++;
                AVLTree.calculateHeight();
                AVLTree.calculateDepth();
                saveState();
            }
            else if(AVLTree.curNode->left&&AVLTree.curNode->right){
                if(!AVLTree.temp) {
                    AVLTree.temp=AVLTree.curNode->left;
                    AVLTree.temp->setHighlight();
                    saveState();
                }
                if(AVLTree.temp->right){
                    AVLTree.temp->deHighlight();
                    AVLTree.temp=AVLTree.temp->right;
                    AVLTree.temp->setHighlight();
                    saveState();
                }
                else{
                    AVLTree.curNode->setValue(AVLTree.temp->getValue());
                    AVLTree.curNode->deHighlight();
                    AVLTree.curNode=AVLTree.temp;
                }
            }
            else if(AVLTree.curNode->left){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->left;
                    else AVLTree.curNode->parent->right = AVLTree.curNode->left;
                }
                else{
                    AVLTree.root=AVLTree.curNode->left;
                }
                AVLTree.curNode->left->parent = AVLTree.curNode->parent;
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->left;
                delete del;
                AVLTree.calculateHeight();
                AVLTree.calculateDepth();
                saveState();
            }
            else if(AVLTree.curNode->right){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->right;
                    else AVLTree.curNode->parent->right = AVLTree.curNode->right;
                }
                else{
                    AVLTree.root=AVLTree.curNode->right;
                }
                AVLTree.curNode->right->parent = AVLTree.curNode->parent;
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->right;
                delete del;
                AVLTree.calculateHeight();
                AVLTree.calculateDepth();
                saveState();
            }
        }   
        else if(AVLTree.animationStep==3){
            if (AVLTree.curNode) {
                AVLTree.curNode->setHighlight();
                saveState();
                int balanceFactor=getBalanceFactor(AVLTree.curNode);
                if(abs(balanceFactor)>1){
                    if(balanceFactor>1){
                        if(getBalanceFactor(AVLTree.curNode->left)<0) AVLTree.rotateLeftRight(AVLTree.curNode);
                        else AVLTree.rotateRight(AVLTree.curNode);
                    }
                    else if(balanceFactor<-1){
                        if(getBalanceFactor(AVLTree.curNode->right)>0) AVLTree.rotateRightLeft(AVLTree.curNode);
                        else AVLTree.rotateLeft(AVLTree.curNode);
                    }
                    AVLTree.setArrowDestination();
                    AVLTree.animationStep++;
                    saveState();
                }
                else {
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        AVLTree.animationStep=0;
                        saveState();
                        currentStep=0;
                        applyState();
                        return;
                    }
                }
            }
        }
        else if(AVLTree.animationStep==4){
            AVLTree.animationStep++;
            AVLTree.setPosition();
        }
        else if(AVLTree.animationStep==5){
            AVLTree.setArrowDestination();
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::saveSearchState(int value){
    saveState();
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
        saveState();
    }
    while (AVLTree.animationStep==1){
        if(!AVLTree.curNode||value==AVLTree.curNode->getValue()){
            AVLTree.animationStep=0;
            animationState=AVLAnimationMode::IDLE;
            AVLTree.curNode=AVLTree.root;
            saveState();
            currentStep=0;
            applyState();
            return;
        }
        if(AVLTree.curNode) AVLTree.curNode->deHighlight();
        if(value<AVLTree.curNode->getValue()){
            AVLTree.curNode=AVLTree.curNode->left;    
        }
        else{
            AVLTree.curNode=AVLTree.curNode->right;
        }
        if(AVLTree.curNode){
            AVLTree.curNode->setHighlight();
            if(AVLTree.curNode&&value!=AVLTree.curNode->getValue()){
                saveState();
            }
        }
    }
}

void AVLState::animateInsert(int value){
    if(!isPlaying||isPaused) return;
    if(!AVLTree.root){
        AVLTree.root = new AVLNode(); 
        AVLTree.root->setValue(value);
        AVLTree.calculateHeight();
        AVLTree.root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
        AVLTree.root->setTargetPosition({(float)GetScreenWidth()/2,AVLPosition.y});
        AVLTree.curNode=AVLTree.root;
        animationState=AVLAnimationMode::IDLE;
        currentStep++;
        return;
    }
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            currentStep++;
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                if(!AVLTree.curNode->left){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->left;
                }
            }
            else{
                if(!AVLTree.curNode->right){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->right;
                }
            }
            AVLTree.curNode->setHighlight();
            checkTimer=0;
        }
    }
    else if(AVLTree.animationStep==2){
        if(value<AVLTree.curNode->getValue()){
            AVLTree.curNode->left=new AVLNode();
            AVLTree.curNode->left->setPosition(AVLTree.curNode->getOrigin());
            AVLTree.curNode->left->setValue(value);
            AVLTree.curNode->left->parent=AVLTree.curNode;
        }
        else{
            AVLTree.curNode->right=new AVLNode();
            AVLTree.curNode->right->setPosition(AVLTree.curNode->getOrigin());
            AVLTree.curNode->right->setValue(value);
            AVLTree.curNode->right->parent=AVLTree.curNode;
        }
        AVLTree.calculateHeight();
        AVLTree.setTargetPosition();
        AVLTree.curNode->deHighlight();
        AVLTree.animationStep++;
    }
    else if(AVLTree.animationStep==3){
        if(value<AVLTree.curNode->getValue()){
            AVLTree.curNode->left->setHighlight();
            AVLTree.curNode->setDestinationLeft(AVLTree.curNode->left->getOrigin());
            if(AVLTree.checkPosition()){         
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->left;
            }
        }
        else{
            AVLTree.curNode->right->setHighlight();
            AVLTree.curNode->setDestinationRight(AVLTree.curNode->right->getOrigin());
            if(AVLTree.checkPosition()){
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->right;
            }
        }
    }
    else if(AVLTree.animationStep==4){
        if (AVLTree.curNode) {
            AVLTree.curNode->setHighlight();
            int balanceFactor=getBalanceFactor(AVLTree.curNode);
            if(abs(balanceFactor)>1){
                currentStep++;
                if(balanceFactor>1){
                    if(getBalanceFactor(AVLTree.curNode->left)<0) AVLTree.rotateLeftRight(AVLTree.curNode);
                    else AVLTree.rotateRight(AVLTree.curNode);
                }
                else if(balanceFactor<-1){
                    if(getBalanceFactor(AVLTree.curNode->right)>0) AVLTree.rotateRightLeft(AVLTree.curNode);
                    else AVLTree.rotateLeft(AVLTree.curNode);
                }
                AVLTree.animationStep++;
                currentStep++;
            }
            else {
                checkTimer += GetFrameTime();
                if (checkTimer >= delayTime) {
                    currentStep++;
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        checkTimer=0;
                        isPlaying=false;
                        isPaused=true;
                        AVLTree.animationStep=0;
                        currentStep++;
                        return;
                    }
                    checkTimer = 0;
                }
            }
        }
    }
    else if(AVLTree.animationStep==5){
        if(AVLTree.checkArrowDestination()){
            AVLTree.animationStep++;
            AVLTree.setTargetPosition();
        }
    }
    else if(AVLTree.animationStep==6){
        if(AVLTree.checkPosition()){
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::animateRemove(int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
        currentStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            if(!AVLTree.curNode){
                AVLTree.animationStep=0;
                animationState=AVLAnimationMode::IDLE;
                AVLTree.curNode=AVLTree.root;
                checkTimer=0;
                currentStep++;
                isPlaying=false;
                isPaused=true;
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value==AVLTree.curNode->getValue()){
                AVLTree.animationStep++;
            }
            else if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
            }
            checkTimer=0;
            currentStep++;
        }
    }    
    else if(AVLTree.animationStep==2){
        if(AVLTree.curNode->isLeaf()){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = nullptr;
                else AVLTree.curNode->parent->right = nullptr;
                AVLTree.curNode=AVLTree.curNode->parent;
                delete del;
            }
            else {
                AVLTree.root = nullptr;
                delete del;
                AVLTree.curNode=nullptr;
            }
            AVLTree.animationStep++;
            AVLTree.calculateHeight();
            AVLTree.calculateDepth();
            currentStep++;
        }
        else if(AVLTree.curNode->left&&AVLTree.curNode->right){
            if(!AVLTree.temp) {
                AVLTree.temp=AVLTree.curNode->left;
                AVLTree.temp->setHighlight();
                currentStep++;
            }
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                if(AVLTree.temp->right){
                    AVLTree.temp->deHighlight();
                    AVLTree.temp=AVLTree.temp->right;
                    AVLTree.temp->setHighlight();
                    currentStep++;
                }
                else{
                    AVLTree.curNode->setValue(AVLTree.temp->getValue());
                    AVLTree.curNode->deHighlight();
                    AVLTree.curNode=AVLTree.temp;
                }
                checkTimer=0;
            }
        }
        else if(AVLTree.curNode->left){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->left;
                else AVLTree.curNode->parent->right = AVLTree.curNode->left;
            }
            else{
                AVLTree.root=AVLTree.curNode->left;
            }
            AVLTree.curNode->left->parent = AVLTree.curNode->parent;
            AVLTree.animationStep++;
            AVLTree.curNode=AVLTree.curNode->left;
            delete del;
            AVLTree.calculateHeight();
            AVLTree.calculateDepth();
            currentStep++;
        }
        else if(AVLTree.curNode->right){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->right;
                else AVLTree.curNode->parent->right = AVLTree.curNode->right;
            }
            else{
                AVLTree.root=AVLTree.curNode->right;
            }
            AVLTree.curNode->right->parent = AVLTree.curNode->parent;
            AVLTree.animationStep++;
            AVLTree.curNode=AVLTree.curNode->right;
            delete del;
            AVLTree.calculateHeight();
            AVLTree.calculateDepth();
            currentStep++;
        }
    }
    else if(AVLTree.animationStep==3){ 
        if (AVLTree.curNode) {
            AVLTree.curNode->setHighlight();
            int balanceFactor=getBalanceFactor(AVLTree.curNode);
            if(abs(balanceFactor)>1){
                currentStep++;
                if(balanceFactor>1){
                    if(getBalanceFactor(AVLTree.curNode->left)<0) AVLTree.rotateLeftRight(AVLTree.curNode);
                    else AVLTree.rotateRight(AVLTree.curNode);
                }
                else if(balanceFactor<-1){
                    if(getBalanceFactor(AVLTree.curNode->right)>0) AVLTree.rotateRightLeft(AVLTree.curNode);
                    else AVLTree.rotateLeft(AVLTree.curNode);
                }
                AVLTree.animationStep++;
                currentStep++;
            }
            else {
                checkTimer += GetFrameTime();
                if (checkTimer >= delayTime) {
                    currentStep++;
                    AVLTree.curNode->deHighlight();
                    if (!AVLTree.curNode->parent){
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        checkTimer=0;
                        currentStep++;
                        isPlaying=false;
                        isPaused=true;
                        AVLTree.animationStep=0;
                        currentStep++;
                        return;
                    }
                    checkTimer = 0;
                    AVLTree.animationStep++;
                }
            }
        } 
    }
    else if(AVLTree.animationStep==4){
        if(AVLTree.checkArrowDestination()){
            AVLTree.animationStep++;
            AVLTree.setTargetPosition();
        }
    }
    else if(AVLTree.animationStep==5){
        if(AVLTree.checkPosition()){
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::animateSearch(int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
        currentStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            if(!AVLTree.curNode||value==AVLTree.curNode->getValue()){
                AVLTree.animationStep=0;
                animationState=AVLAnimationMode::IDLE;
                AVLTree.curNode=AVLTree.root;
                checkTimer=0;
                currentStep++;
                isPlaying=false;
                isPaused=true;
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
                if(AVLTree.curNode&&value!=AVLTree.curNode->getValue()){
                    currentStep++;
                }
            }
            checkTimer=0;
        }
    }
}

int AVLState::getBalanceFactor(AVLNode* root){
    int balanceFactor=0;
    if(root->left) balanceFactor+=root->left->getHeight();
    if(root->right) balanceFactor-=root->right->getHeight();
    return balanceFactor;
}

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
    AVLTree.clearTree();
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