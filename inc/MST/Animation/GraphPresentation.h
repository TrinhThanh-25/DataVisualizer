#pragma once

#include "GraphSetofOperation.h"
#include "MST/Graph.h"
#include "GUI/CodeBlock.h"
#include "GraphCode.h"
#include <algorithm>
#include <queue>

class GraphPresentation{
    public:
        float & speed;
        Graph * graph;
        std::vector<GraphSetofOperation> SetOperations;
        int currentStep;
        std::vector<std::vector<Graph*>> & historyState;
        std::vector<std::vector<int>> & historyCode;
        int & currentPresentationIndex;
        int & currentStateIndex;
        CodeBlock & codeBlock;
        std::vector<int> parent;
        std::vector<int> rank;

        GraphPresentation(float & speed, Graph * graph,
                            std::vector<std::vector<Graph*>> & historyState, std::vector<std::vector<int>> & historyCode, CodeBlock& codeBlock, int & currentPresentationIndex, int & currentStateIndex);

        void CreateGraph(int numofNode);
        void Kruskal();
        void initDisjointSet(int n);
        int find(int x);
        bool unionSets(int x, int y);
        void Prim(int source);


        bool DrawPresentation();
};