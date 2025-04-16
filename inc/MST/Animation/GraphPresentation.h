#pragma once

#include "GraphSetofOperation.h"
#include "MST/Graph.h"
#include <algorithm>

class GraphPresentation{
    public:
        float & speed;
        Graph * graph;
        std::vector<GraphSetofOperation> SetOperations;
        int currentStep;
        std::vector<int> parent;
        std::vector<int> rank;

        GraphPresentation(float & speed, Graph * graph);

        void CreateGraph(int numofNode);
        void Kruskal();
        void initDisjointSet(int n);
        int find(int x);
        bool unionSets(int x, int y);


        bool DrawPresentation();
};