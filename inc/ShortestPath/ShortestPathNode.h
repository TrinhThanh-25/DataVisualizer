#ifndef SHORTESTPATHNODE_H
#define SHORTESTPATHNODE_H

#include <vector>
#include <algorithm>

#include "GUI/Resources.h"
#include "ShortestPath/STArrow.h"

class ShortestPathNode{
    public:
        ShortestPathNode();
        ShortestPathNode(int id);
        ~ShortestPathNode();
        void addAdj(ShortestPathNode* node);
        std::vector<ShortestPathNode*> getAdj();
        void setID(int id);
        int getID();
        void setCost(int cost);
        int getCost();
        void setVisited();
        void deVisited();
        bool getVisited();
        void setKnown();
        void deKnown();
        bool getKnown();
        Vector2 getPosition();
        void setPosition(Vector2 position);
        void addEdge(ShortestPathNode* node);
        void removeEdge(ShortestPathNode* node);
        void clearEdges();

        void update();
        void draw(bool isWeighted, bool isDirected);


    private:
        Rectangle node;
        Vector2 position;

        std::vector<ShortestPathNode*> adj;
        std::vector<STArrow*> arrow;
        int id;
        int cost;
        bool isKnown;
        bool visited;
};

#endif