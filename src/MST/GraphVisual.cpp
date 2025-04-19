#include "MST/GraphVisual.h"
#include <raylib.h>

GraphVisual::GraphVisual(float &speed)
    : speed(speed), graph(new Graph()), presentation(speed, graph), inputPanel(), speedSlider(0.01f, 0.1f, 0.05f, 100) {}

GraphVisual::~GraphVisual() {
    delete graph;
}

void GraphVisual::Draw() {
    inputPanel.draw();
    if (graph) {
        graph->Draw();
    }
    presentation.DrawPresentation();
    speedSlider.Draw();
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

void GraphVisual::PrimAlgo(){
    presentation.Prim();
}

void GraphVisual::Update() {
    inputPanel.setBackActive();
    inputPanel.update();
    speedSlider.Update();
    speed = speedSlider.val;
    
    if(IsKeyPressed(KEY_C)){
        CreateGraph(13);
    }
    // Xử lý tải file
    if (inputPanel.IsLoadFilePressed()) {
        auto fileValues = inputPanel.GetFileValues2D();
        if (!fileValues.empty()) {
            std::cout<<"Co do day\n";
            for(int i = 0; i < fileValues.size(); i++){
                for(int j = 0; j < fileValues[i].size(); j++){
                    std::cout<<fileValues[i][j]<<" ";
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
            CreateGraphFromInput(fileValues);
            inputPanel.ResetInputState();
        } else {
            std::cout << "Loi file rui nghennn\n";
        }
        //inputPanel.ResetInputState();
    }

    // Xử lý các nút thuật toán khác
    if (inputPanel.isAnyButtonPressed()) {
        int activeButtonIndex = inputPanel.GetActiveButtonIndex();
        if(activeButtonIndex == 0){
            if (inputPanel.showInputBox && inputPanel.randomButton.isPressed()) {
                int inputValue = inputPanel.GetInputText();
                std::cout << "So dinh: " << inputValue << std::endl;
                if (inputValue > 0) {
                    CreateGraph(inputValue);
                    // Không gọi ResetInputState để giữ giao diện
                    inputPanel.ResetInputState();
                } else {
                    std::cout << "Lỗi: Số đỉnh phải lớn hơn 0. Vui lòng nhập số nguyên dương vào ô nhập liệu.\n";
                }
            }
            std::cout<<"Ra toi day ui"<<std::endl;
        }
        else if(activeButtonIndex == 1){
            KruskalAlgo();
            inputPanel.ResetInputState();
        }
        else if (activeButtonIndex == 2) {
            
                PrimAlgo();
                inputPanel.ResetInputState();
            
        } else {
            std::cout << "loi o duoi nay noeee " << activeButtonIndex << ")\n";
        }
        //inputPanel.ResetInputState();
    }
    //inputPanel.ResetInputState();

    if (graph) {
        graph->Update();
    }
}