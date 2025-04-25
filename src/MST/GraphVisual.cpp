#include "MST/GraphVisual.h"
#include <raylib.h>
#include <random>

GraphVisual::GraphVisual(float &speed)
    : speed(speed), graph(new Graph()), currentPresentationIndex(-1), currentStateIndex(0), historyState({}), historyCode({}), codeBlock(), presentation(speed, graph, historyState, historyCode, codeBlock, currentPresentationIndex, currentStateIndex), inputPanel(), speedSlider(0.1, 5.0f, 1.0f, 100) {
        inputPanel.setDataName("Min Spanning Tree");
    }

GraphVisual::~GraphVisual() {
    delete graph;
}

void GraphVisual::Draw() {
    inputPanel.draw();
    codeBlock.draw();
    
    

    speedSlider.Draw();

    if (graph) {
        if(this->isRewinding){
            codeBlock.setHighlight({historyCode[currentPresentationIndex][currentStateIndex]});
            historyState[currentPresentationIndex][currentStateIndex]->Draw();
        }
        else{
            if(isDrawGraph){
                graph->Draw();
            }
        }
    }
}

void GraphVisual::CreateGraph(int numOfVer) {
    graph->createGraph(numOfVer);
    presentation.CreateGraph(numOfVer);
}

void GraphVisual::CreateGraphFromInput(std::vector<std::vector<int>> input){
    graph->CreateGraphFromInput(input);
    presentation.CreateGraph(input[0][0]);
}

void GraphVisual::KruskalAlgo(){
    presentation.Kruskal();
}

void GraphVisual::PrimAlgo(int source){
    presentation.Prim(source);
}

void GraphVisual::Update() {
    inputPanel.setBackActive();
    inputPanel.update();
    speedSlider.Update();

    
    if(inputPanel.keyboardButton.isPressed()){
        auto fileValues = inputPanel.GetFileValues2D();
        if(!fileValues.empty()){
            presentation.SetOperations.clear();
            CreateGraphFromInput(fileValues);
            this->isPlaying = true;
            inputPanel.ResetInputState();
        }
    }
    
    
    // Xử lý tải file
    if (inputPanel.IsLoadFilePressed()) {
        auto fileValues = inputPanel.GetFileValues2D();
        if (!fileValues.empty()) {
            std::cout<<"Co do day trong file neeeee\n";
            for(int i = 0; i < fileValues.size(); i++){
                for(int j = 0; j < fileValues[i].size(); j++){
                    std::cout<<fileValues[i][j]<<" ";
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
            presentation.SetOperations.clear();
            CreateGraphFromInput(fileValues);
            this->isPlaying = true;
            inputPanel.ResetInputState();
        } else {
            std::cout << "Loi file rui nghennn\n";
        }
        //inputPanel.ResetInputState();
    }
    
    

    // Xử lý các nút thuật toán khác
    if (inputPanel.isAnyButtonPressed()) {
        int activeButtonIndex = inputPanel.GetActiveButtonIndex();
        auto inputValue = inputPanel.GetInputText();
        std::cout<<inputValue<<std::endl;
        if(activeButtonIndex == 0){
            if (inputPanel.showInputBox && inputPanel.randomButton.isPressed()) {
                std::random_device rd; // Tạo seed
                std::mt19937 gen(rd()); // Engine ngẫu nhiên
                std::uniform_int_distribution<> dis(3, 13); // Khoảng [1, 100]

                int inputValue = dis(gen); // Random một số

                std::cout << "So dinh: " << inputValue << std::endl;
                if (inputValue > 0) {
                    presentation.SetOperations.clear();
                    CreateGraph(inputValue);
                    this->isPlaying = true;
                    // Không gọi ResetInputState để giữ giao diện
                    inputPanel.ResetInputState();
                } else {
                    std::cout << "Lỗi: Số đỉnh phải lớn hơn 0. Vui lòng nhập số nguyên dương vào ô nhập liệu.\n";
                }
            }


            std::cout<<"Ra toi day ui"<<std::endl;
        }
        else if(activeButtonIndex == 1){
            lastactiveButton = activeButtonIndex;
            lastinputValue = inputValue;
            presentation.SetOperations.clear();
            graph->ResetGraphColor();
            KruskalAlgo();
            this->isPlaying = true;
            inputPanel.ResetInputState();
        }
        else if (activeButtonIndex == 2) {
                
                if(inputValue != -1 && inputPanel.Apply.isPressed()){
                    lastactiveButton = activeButtonIndex;
                    lastinputValue = inputValue;
                    presentation.SetOperations.clear();
                    graph->ResetGraphColor();
                    PrimAlgo(inputValue);
                    this->isPlaying = true;
                    inputPanel.ResetInputState();
                }
            
            
        } else {
            std::cout << "loi o duoi nay noeee " << activeButtonIndex << ")\n";
        }
        //inputPanel.ResetInputState();
    }
    //inputPanel.ResetInputState();

    if(isPlaying){
        isRewinding = false;
        if(inputPanel.isEndPressed()){
            isSkipBack = true;
        }

        if(isSkipBack){
            isDrawGraph = false;
            speed = 2.0f;
        }
        else{
            speed = speedSlider.val * 0.02f;
        }
    }
    else{
        speed = speedSlider.val * 0.02f;
        // std::cout<<"PresentationCur: "<<currentPresentationIndex<<std::endl;
        // std::cout<<"StateCur: "<<currentStateIndex<<std::endl; 
        if(inputPanel.isNextPressed()){
            this->isRewinding = true;
            currentStateIndex++;
            if(currentStateIndex == historyState[currentPresentationIndex].size()){
                currentPresentationIndex++;
                currentStateIndex = 0;
                if(currentPresentationIndex == historyState.size()){
                    this->isRewinding = false;
                    currentPresentationIndex = historyState.size() - 1;
                    currentStateIndex = historyState.back().size() - 1;
                }
            }
        }
        else if(inputPanel.isEndPressed()){
            std::cout<<"Size: "<<historyState.size()<<std::endl;
            this->isRewinding = false;
            currentPresentationIndex = historyState.size() - 1;
            currentStateIndex = historyState.back().size() - 1;
        }
        else if(inputPanel.isPrevPressed()){
            this->isRewinding = true;
            currentStateIndex--;
            if(currentStateIndex < 0){
                currentPresentationIndex--;
                if(currentPresentationIndex < 0){
                    currentPresentationIndex = 0;
                    currentStateIndex = 0;
                }
                else{
                    currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                }
            }
        }
        else if(inputPanel.isStartPressed()){
            this->isRewinding = true;
            currentPresentationIndex--;
            if(currentPresentationIndex < 0){
                currentPresentationIndex = 0;
            }
            currentStateIndex = historyState[currentPresentationIndex].size() - 1;
        }
    }

    if(IsKeyPressed(KEY_R)){
        switch (lastactiveButton)
        {
        case 1: {graph->ResetGraphColor(); presentation.SetOperations.clear(); KruskalAlgo(); this->isPlaying = true; break;}
        case 2: {graph->ResetGraphColor(); presentation.SetOperations.clear(); if(lastinputValue != -1) PrimAlgo(lastinputValue); this->isPlaying = true;}
        }
    }
    if(IsKeyPressed(KEY_SPACE)){
        this->isPlaying = !this->isPlaying;
    }
    if(inputPanel.isPlayPressed()){
        if(!historyState.empty() && this->isPlaying == false && presentation.currentStep == 0 && lastactiveButton != 0){
            switch (lastactiveButton)
            {
            case 1: {graph->ResetGraphColor(); presentation.SetOperations.clear(); KruskalAlgo(); this->isPlaying = true; break;}
            case 2: {graph->ResetGraphColor(); presentation.SetOperations.clear(); if(lastinputValue != -1) PrimAlgo(lastinputValue); this->isPlaying = true;}
            }
        }
        else if(this->isPlaying){
            this->isPlaying = false;
        }
        else if(!this->isPlaying){
            this->isPlaying = true;
        }
    }

    if(this->isPlaying){
        if(presentation.DrawPresentation()){
            speed = speedSlider.val * 0.02f;
            this->isPlaying = false;
            isDrawGraph = true;
            isSkipBack = false;
            inputPanel.setEnd();
        }
        else{
            this->isPlaying = true;
            inputPanel.deEnd();
        }
    }

    if(lastactiveButton == 0){
        inputPanel.deEnd();
        inputPanel.setPause();
    }

    if(this->isPlaying){
        inputPanel.dePause();
    }
    else if(!this->isPlaying){
        inputPanel.setPause();
    }



    if (graph) {
        graph->Update();
    }
}

bool GraphVisual::isBackPressed(){
    bool res = inputPanel.isBackPressed();
    if(res){
        inputPanel.reset();
        speedSlider.reset();
        graph = new Graph();
        this->currentPresentationIndex = -1;
        this->currentStateIndex = 0;
        this->isRewinding = false;
        this->isPlaying = true;
    }
    return res;
}