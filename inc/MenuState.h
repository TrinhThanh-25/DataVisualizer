#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GUI/Button.h"

class MenuState{
    public:
        MenuState();

        void isSLLPressed();

        void draw();
        void update();
    public:
        bool isStarted = false;
        bool isSLL = false;
        bool isLinearHT = false;
        bool isTree234 = false;
        bool isAVLTree = false;
        bool isMinSpanningTree = false;
        bool isShortestPath = false;
        bool* isUsed=nullptr;
    private:
        Texture2D background;
        const char* title;
        Button exit;
        Button SLL;
        Button LinearHT;
        Button Tree234;
        Button AVLTree;
        Button MinSpanningTree;
        Button ShortestPath;
};

#endif