#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <vector>

#include "ShortestPath/ShortestPathNode.h"

class ShortestPath{
    public:
        ShortestPath();
        ~ShortestPath();

        void createGraph(int nodes, int edges);
        void addEdge(int node1, int node2);
        void removeEdge(int node1, int node2);
        void searchPath(int startNode, int endNode);
        void clearGraph();
        void resetGraph();
        void setWeighted();
        void deWeighted();
        void setDirected();
        void deDirected();

        void GridBasedPlacement(std::vector<ShortestPathNode*>& graph,int screenWidth, int screenHeight);

        void update();
        void draw();

        void Dijkstra(int startNode);

    private:
        std::vector<ShortestPathNode*> graph;

        bool isWeighted;
        bool isDirected;
};

#endif