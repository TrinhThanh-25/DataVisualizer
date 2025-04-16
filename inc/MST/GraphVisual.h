#pragma once
#include "Graph.h"
#include "MST/Animation/GraphPresentation.h"

class GraphVisual {
public:
    Graph* graph; // Con trỏ thô
    float &speed;
    GraphPresentation presentation;

    GraphVisual(float &speed);
    ~GraphVisual(); // Thêm destructor để giải phóng graph

    void Draw();
    void CreateGraph(int numOfVer);
    void KruskalAlgo();
    void Update();
};