#ifndef SHORTESTPATHNODE_H
#define SHORTESTPATHNODE_H

#include <vector>
#include <algorithm>
#include <GUI/Resources.h>
#include <ShortestPath/STArrow.h>

class ShortestPathNode{
    public:
        ShortestPathNode(Vector2 pos);
        ShortestPathNode(int id);
        ~ShortestPathNode();
        void setID(int id);
        int getID();
        void setCost(int cost);
        int getCost();
        void setHighlight();
        void deHighlight();
        bool getHighlight();
        void setKnown();
        void deKnown();
        bool getKnown();
        Vector2 getPosition();
        void setPosition(Vector2 position);
        Vector2 getForce();
        void setForce(Vector2 force);
        void addEdge(ShortestPathNode* node);
        void removeEdge(ShortestPathNode* node);
        void clearEdges();

        void setChosen();
        bool isCollision(ShortestPathNode* other);
        void applyRepellingForce(ShortestPathNode* other);
        void boundaryCollision();
        bool getBoundaryCollision();

        ShortestPathNode* clone() const;

        void update();
        void updateNode();
        void draw(bool isWeighted, bool isDirected);
        void drawNode();
    public:
        std::vector<ShortestPathNode*> adj;
        std::vector<STArrow*> arrow;

    private:
        Rectangle node;
        Vector2 position;

        Vector2 force;

        Color nodeColor=LIGHTGRAY;
        Color textColor=BLACK;
        Color highlight = RED;
        Color textHighlight = WHITE;
        Color isKnownColor = GREEN;

        bool isChosen=false;
        bool isBoundaryCollision=false;

        int id;
        int cost;
        bool isKnown;
        bool isHighlight;
};

#endif