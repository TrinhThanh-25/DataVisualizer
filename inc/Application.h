#ifndef APPLICATION_H
#define APPLICATION_H

#include <MenuState.h>
#include <SLL/SLLState.h>
#include <AVL/AVLState.h>
#include <ShortestPath/ShortestPathState.h>
#include "HashTableVisual.h"

class Application{
    public:
        Application();
        void run();
    private:
        MenuState menuState;
        SLLState SLL;
        AVLState AVL;
        ShortestPathState ST;
        HashTableVisualization hashTable(fontNumber, fontNumber, true, speed);
};

#endif