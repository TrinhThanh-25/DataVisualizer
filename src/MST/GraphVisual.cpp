#include "MST/GraphVisual.h"
#include <raylib.h>

GraphVisual::GraphVisual(float &speed)
    : speed(speed), graph(new Graph()), presentation(speed, graph) {}

GraphVisual::~GraphVisual() {
    delete graph;
}

void GraphVisual::Draw() {
    if (graph) {
        graph->Draw();
    }
    presentation.DrawPresentation();
}

void GraphVisual::CreateGraph(int numOfVer) {
    presentation.CreateGraph(numOfVer);
}

void GraphVisual::KruskalAlgo(){
    presentation.Kruskal();
}

void GraphVisual::PrimAlgo(){
    //presentation.Prim();
}

void GraphVisual::Update() {
    if (IsKeyPressed(KEY_C)) {
        CreateGraph(13);
    }
    if(IsKeyPressed(KEY_K)){
        KruskalAlgo();
    }
    if(IsKeyPressed(KEY_P)){
        PrimAlgo();
    }
    if (graph) {
        graph->Update();
    }
}