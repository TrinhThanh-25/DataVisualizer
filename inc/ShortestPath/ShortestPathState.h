#ifndef SHORTESTPATHSTATE_H
#define SHORTESTPATHSTATE_H

#include<random>

#include "ShortestPath/ShortestPath.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "GUI/Panel.h"
#include "GUI/CodeBlock.h"

class ShortestPathState{
    public:
        ShortestPathState();
        void update();
        void draw();

        void resetBox();
        std::string getRandomInput(int nodes);

    private:
        ShortestPath ST;
        CodeBlock STCode;
        Panel panel;

        InputBox NodesBox;
        InputBox EdgesBox;
        InputBox StartNodesBox;

        Button Random;
        Button LoadFile;
        Button Apply;
        
        Button Weighted;
        Button Directed;
        Button Unweighted;
        Button Undirected;
};

#endif