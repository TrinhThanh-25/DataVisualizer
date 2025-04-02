//CẦN FIX LOGIC KHI LƯU STATE(1 SỐ STATE KHÔNG CHẠY TIẾP ĐƯỢC)
//FIX KHI PRESS BACK GIỮA CHỪNG BỊ LỖI
//KIỂM TRA LẠI CÁC HÀM CLONE

#include "ShortestPath/ShortestPathState.h"

const float COOLDOWN=0.93f;

ShortestPathState::ShortestPathState() : NodesBox(120,700,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor), EdgesBox(120,850,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor), StartNodesBox(120,700,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor){
    this->Random.setText("Random",STButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",STButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",STButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    this->Weighted.setText("Weighted",STButtonFontSize);
    this->Weighted.setSize({120, 30});
    this->Weighted.setPosition({180,700});
    this->Weighted.setColor(panelNormal,panelHovered,panelPressed);
    this->Weighted.setRectangle();

    this->Unweighted.setText("Unweighted",STButtonFontSize);
    this->Unweighted.setSize({120, 30});
    this->Unweighted.setPosition({320,700});
    this->Unweighted.setColor(panelNormal,panelHovered,panelPressed);
    this->Unweighted.setRectangle();

    this->Directed.setText("Directed",STButtonFontSize);
    this->Directed.setSize({120, 30});
    this->Directed.setPosition({180,740});
    this->Directed.setColor(panelNormal,panelHovered,panelPressed);
    this->Directed.setRectangle();

    this->Undirected.setText("UnDirected",STButtonFontSize);
    this->Undirected.setSize({120, 30});
    this->Undirected.setPosition({320,740});
    this->Undirected.setColor(panelNormal,panelHovered,panelPressed);
    this->Undirected.setRectangle();
    
    this->Undirected.Selected();
    this->Unweighted.Selected();
    ST.deDirected();
    ST.deWeighted();

    NodesBox.setNameBox("Number Of Vertices");
    EdgesBox.setNameBox("Number Of Edges");
    StartNodesBox.setNameBox("Start Node");
}

void ShortestPathState::update(){
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

    ST.update();
    panel.update();
    code.update();

    switch (animationState) {
        case STAnimationMode::CREATE:
            animateFruchtermanReingold();
            break;
        case STAnimationMode::DIJKSTRA:
            if (!isStateSaved) {
                saveDijkstraState(std::stoi(startNodeText));
                isStateSaved = true; 
            }
            animateDijkstra(std::stoi(startNodeText));
            break;
        case STAnimationMode::IDLE:
            break;
        default:
            break;
    }

    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isDijkstraUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isSettingUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.setActive();
        Unweighted.setActive();
        Directed.setActive();
        Undirected.setActive();
    }
    if(Random.isPressed()){
        int numNodes=rand()%9+2;
        NodesBox.setText(std::to_string(numNodes));
        EdgesBox.setText(std::to_string(rand()%(numNodes*(numNodes-1))/2+1));
    }
    else if(LoadFile.isPressed()){
        //createBox.setText(loadFileContent());
    }
    else if(Weighted.isPressed()){
        Weighted.Selected();
        Unweighted.deSelected();
        ST.setWeighted();
    }
    else if(Unweighted.isPressed()){
        Unweighted.Selected();
        Weighted.deSelected();
        ST.deWeighted();
    }
    else if(Directed.isPressed()){
        Directed.Selected();
        Undirected.deSelected();
        ST.setDirected();
    }
    else if(Undirected.isPressed()){
        Undirected.Selected();
        Directed.deSelected();
        ST.deDirected();
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        startNodeText=StartNodesBox.GetText();
        ST.deltaTime=0;
        if(panel.isCreateUsed()&&NodesBox.GetText()!=""&&EdgesBox.GetText()!=""){
            ST.createGraph(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
            animationState=STAnimationMode::CREATE;
        }
        else if(panel.isDijkstraUsed()&&StartNodesBox.GetText()!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=STAnimationMode::DIJKSTRA;
        }
        resetBox();
    }
    else if(panel.isBackPressed()){
        ST.clearGraph();
        resetBox();
        Unweighted.Selected();
        Undirected.Selected();
        Weighted.deSelected();
        Directed.deSelected();
        ST.deDirected();
        ST.deWeighted();
    }
    else if(panel.isAnyButtonPressed()){
        resetBox();
    }
    if(panel.isCreateUsed()){
        NodesBox.Update();
        EdgesBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Update();
    }
    else if(panel.isSettingUsed()){
        this->Weighted.update();
        this->Unweighted.update();
        this->Directed.update();
        this->Undirected.update();
    }
}

void ShortestPathState::draw(){
    code.draw();
    ST.draw();
    panel.draw();
    DrawText("Shortest Path",GetScreenWidth()/2.0f-MeasureText("Shortest Path",dataTitleFontSize)/2.0f,dataTitlePosition.y-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    STCode.draw();
    if(panel.isCreateUsed()){
        NodesBox.Draw();
        EdgesBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->LoadFile.drawRectangleRounded(100);
        this->Apply.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Draw();
    }
    else if(panel.isSettingUsed()){
        Weighted.drawRectangleRounded(100);
        Directed.drawRectangleRounded(100);
        Unweighted.drawRectangleRounded(100);
        Undirected.drawRectangleRounded(100);
        Weighted.drawText(panelSubButtonTextColor);
        Directed.drawText(panelSubButtonTextColor);
        Unweighted.drawText(panelSubButtonTextColor);
        Undirected.drawText(panelSubButtonTextColor);
    }
}

void ShortestPathState::saveDijkstraState(int startNode){
    while(true){
        if(ST.animationStep==0){
            ST.resetGraph();
            saveState();
            ST.current=ST.graph[startNode];
            ST.animationStep++;
            ST.graph[startNode]->setCost(0);
            saveState();
        }
        else if(ST.animationStep==1){
            ST.current->setHighlight();
            ST.animationStep++;
            saveState();
        }
        else if(ST.animationStep==2){
            if(ST.isDirected){
                if(ST.current->arrow.empty()){
                    ST.current->setKnown();
                    ST.animationStep++;
                    saveState();
                    continue;
                }
                ST.current->arrow[ST.index]->setHighlight();
                saveState();
                int to = ST.current->arrow[ST.index]->getTo();
                int weight = (ST.isWeighted) ? ST.current->arrow[ST.index]->getWeight() : 1;
                int newCost = ST.current->getCost() + weight;
    
                if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                    ST.graph[to]->setCost(newCost);
                    saveState();
                }
                ST.current->arrow[ST.index]->deHighlight();
                ST.index++;
    
                if(ST.index>=ST.current->arrow.size()){
                    ST.index=0;
                    ST.animationStep++;
                    ST.current->setKnown();
                    saveState();
                }
            }
            else{
                int from = ST.allArrows[ST.index]->getFrom();
                int to = ST.allArrows[ST.index]->getTo();
                int weight = (ST.isWeighted)? ST.allArrows[ST.index]->getWeight() : 1;
                if(from == ST.current->getID()||to == ST.current->getID()){
                    ST.allArrows[ST.index]->setHighlight();
                    saveState();
                    int newCost = ST.current->getCost() + weight;
                    if (from == ST.current->getID()) {
                        if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                            ST.graph[to]->setCost(newCost);
                            saveState();
                        }
                    } else if (to == ST.current->getID()) {
                        if (ST.current->getCost()!=-1&&(ST.graph[from]->getCost() == -1 || newCost < ST.graph[from]->getCost())) {
                            ST.graph[from]->setCost(newCost);
                            saveState();
                        }
                    }
                    ST.allArrows[ST.index]->deHighlight();
                    ST.index++;
                }
                else{
                    ST.index++;
                }
                if(ST.index>=ST.allArrows.size()){
                    ST.index=0;
                    ST.animationStep++;
                    ST.current->setKnown();
                    saveState();
                }
            }
        }
        else if(ST.animationStep==3){
            for (auto n : ST.graph) {
                n->setHighlight();
                if (!n->getKnown() && ((n->getCost() == -1 && minCost==INT_MAX)||(n->getCost()!=-1 && n->getCost() <= minCost))) {
                    if(n->getCost()!=-1)
                        minCost = n->getCost();
                    findSmall = n->getID();
                }
            }
            if (findSmall == -1) {
                for (auto n : ST.graph){
                    n->deKnown();
                    n->deHighlight();
                }
                ST.animationStep=0;
                ST.index=0;
                animationState=STAnimationMode::IDLE;
                saveState();
                currentStep=0;
                applyState();
                return;
            }
            else{
                ST.current = ST.graph[findSmall];
                ST.animationStep-=2;
                saveState();
            }
            findSmall = -1;
            minCost = INT_MAX;
            for (auto n : ST.graph){
                if(n!=ST.current)
                    n->deHighlight();
            }
        }
    }
}
        
void ShortestPathState::animateFruchtermanReingold() {
    float X_min = centerX - rangeX / 2.0f, X_max = centerX + rangeX / 2.0f;
    float Y_min = centerY - rangeY / 2.0f, Y_max = centerY + rangeY / 2.0f;

    if (ST.deltaTime <= 8.0f) {
        ST.deltaTime += GetFrameTime();
        for (auto& node : ST.graph) {
            node->setForce({0, 0});
        }
        for (int i = 0; i < ST.graph.size(); i++) {
            if (!ST.graph[i]) continue;
            for (int j = i + 1; j < ST.graph.size(); j++) {
                if (!ST.graph[j]) continue;
                Vector2 force = ST.ComputeRepulsiveForce(ST.graph[i], ST.graph[j]);
                ST.graph[i]->setForce({ST.graph[i]->getForce().x + force.x,ST.graph[i]->getForce().y + force.y});
                ST.graph[j]->setForce({ST.graph[j]->getForce().x - force.x,ST.graph[j]->getForce().y - force.y});
            }
            for (auto& edge : ST.graph[i]->arrow) {
                int from = edge->getFrom();
                int to = edge->getTo();
                Vector2 force = ST.ComputeAttractiveForce(ST.graph[from], ST.graph[to]);
                ST.graph[from]->setForce({ST.graph[from]->getForce().x - force.x,ST.graph[from]->getForce().y - force.y});
                ST.graph[to]->setForce({ST.graph[to]->getForce().x + force.x,ST.graph[to]->getForce().y + force.y});
            }
        }
        float epsilon = 0.3f;
        float maxDisplacement = 10.0f;
        bool allStable = true;

        for (auto& node : ST.graph) {
            Vector2 force = node->getForce();
            float dx = force.x * ST.cool;
            float dy = force.y * ST.cool;
            float disp = sqrt(dx * dx + dy * dy);
            if (disp > maxDisplacement) {
                dx = dx / disp * maxDisplacement;
                dy = dy / disp * maxDisplacement;
            }
            if (fabs(dx) < epsilon) dx = 0;
            if (fabs(dy) < epsilon) dy = 0;
            float newX = node->getPosition().x + dx;
            float newY = node->getPosition().y + dy;
            newX = std::max(X_min, std::min(newX, X_max));
            newY = std::max(Y_min, std::min(newY, Y_max));
            if (dx != 0 || dy != 0) {
                node->setPosition({newX, newY});
                allStable = false;
            }
        }
        if (allStable || ST.deltaTime > 8.0f) {
            ST.cool = 1.5;
            ST.deltaTime = 0;
            animationState = STAnimationMode::IDLE;
            return;
        }

        ST.cool *= COOLDOWN;
    }
    else {
        ST.cool = 1.5;
        ST.deltaTime = 0;
        animationState = STAnimationMode::IDLE;
        return;
    }
}

void ShortestPathState::animateDijkstra(int startNode){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(ST.animationStep==0){
        ST.resetGraph();
        currentStep++;
        ST.current=ST.graph[startNode];
        ST.animationStep++;
        ST.graph[startNode]->setCost(0);
        currentStep++;
    }
    else if(ST.animationStep==1){
        ST.current->setHighlight();
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            ST.animationStep++;
            currentStep++;
        }
    }
    else if(ST.animationStep==2){
        if(ST.isDirected){
            if(ST.current->arrow.empty()){
                ST.current->setKnown();
                ST.animationStep++;
                currentStep++;
                return;
            }
            checkTimer+=GetFrameTime();
            ST.current->arrow[ST.index]->setHighlight();
            int to = ST.current->arrow[ST.index]->getTo();
            int weight = (ST.isWeighted) ? ST.current->arrow[ST.index]->getWeight() : 1;
            int newCost = ST.current->getCost() + weight;
            if(checkTimer>=delayTime){
                currentStep++;
                checkTimer=0;
                if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                    ST.graph[to]->setCost(newCost);
                    currentStep++;
                }
                ST.current->arrow[ST.index]->deHighlight();
                ST.index++;
            }
            if(ST.index>=ST.current->arrow.size()){
                ST.index=0;
                ST.animationStep++;
                ST.current->setKnown();
                currentStep++;
            }
        }
        else{
            int from = ST.allArrows[ST.index]->getFrom();
            int to = ST.allArrows[ST.index]->getTo();
            int weight = (ST.isWeighted)? ST.allArrows[ST.index]->getWeight() : 1;
            if(from == ST.current->getID()||to == ST.current->getID()){
                checkTimer+=GetFrameTime();
                ST.allArrows[ST.index]->setHighlight();
                if(checkTimer>=delayTime){
                    currentStep++;
                    checkTimer=0;
                    int newCost = ST.current->getCost() + weight;
                    if (from == ST.current->getID()) {
                        if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                            ST.graph[to]->setCost(newCost);
                            currentStep++;
                        }
                    } else if (to == ST.current->getID()) {
                        if (ST.current->getCost()!=-1&&(ST.graph[from]->getCost() == -1 || newCost < ST.graph[from]->getCost())) {
                            ST.graph[from]->setCost(newCost);
                            currentStep++;
                        }
                    }
                    ST.allArrows[ST.index]->deHighlight();
                    ST.index++;
                }
            }
            else{
                ST.index++;
            }
            if(ST.index>=ST.allArrows.size()){
                ST.index=0;
                ST.animationStep++;
                ST.current->setKnown();
                currentStep++;
            }
        }
    }
    else if(ST.animationStep==3){
        checkTimer+=GetFrameTime();
        for (auto n : ST.graph) {
            n->setHighlight();
            if (checkTimer>=delayTime&&!n->getKnown() && ((n->getCost() == -1 && minCost==INT_MAX)||(n->getCost()!=-1 && n->getCost() <= minCost))) {
                if(n->getCost()!=-1)
                    minCost = n->getCost();
                findSmall = n->getID();
            }
        }
        if(checkTimer>=delayTime){
            checkTimer=0;
            if (findSmall == -1) {
                for (auto n : ST.graph){
                    n->deKnown();
                    n->deHighlight();
                }
                ST.animationStep=0;
                ST.index=0;
                animationState=STAnimationMode::IDLE;
                isPlaying=false;
                isPaused=true;
                currentStep++;
                return;
            }
            else{
                ST.current = ST.graph[findSmall];
                ST.animationStep-=2;
                currentStep++;
            }
            findSmall = -1;
            minCost = INT_MAX;
            for (auto n : ST.graph){
                if(n!=ST.current)
                    n->deHighlight();
            }
        }
    }
}

void ShortestPathState::resetBox(){
    NodesBox.resetBox();
    EdgesBox.resetBox();
    StartNodesBox.resetBox();
}

bool ShortestPathState::isBackPressed(){
    return panel.isBackPressed();
}

void ShortestPathState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void ShortestPathState::pause() {
    isPaused = true;  
}

void ShortestPathState::resume() {
    isPaused = false;
}

void ShortestPathState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void ShortestPathState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void ShortestPathState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void ShortestPathState::moveEnd(){
    isPlaying=false;
    isPaused=true;
    currentStep=stateList.size()-1;
    applyState();
}

void ShortestPathState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void ShortestPathState::saveState(){
    ShortestPath* currentState = ST.clone();
    STAnimationMode currentMode = this->animationState;
    stateList.push_back(new AnimationStep{currentState, currentMode});
}

void ShortestPathState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    ST.clearGraph();
    ST = *stateList[currentStep]->ST->clone();
    animationState=stateList[currentStep]->animationState;
}

void ShortestPathState::clearState() {
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}