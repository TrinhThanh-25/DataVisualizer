#ifndef APPLICATION_H
#define APPLICATION_H

#include <MenuState.h>
#include <SLL/SLLState.h>
#include <AVL/AVLState.h>
#include <GUI/Resources.h>
#include <ShortestPath/ShortestPathState.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <HashTable/HashTableVisual.h>
#include <GUI/ColorThemeManager.h>
=======
#include "HashTable/HashTableVisual.h"
>>>>>>> 57ca819e1282dcd2198f5aff20a8ea3daa1dcb55
=======
#include "HashTable/HashTableVisual.h"
>>>>>>> 57ca819e1282dcd2198f5aff20a8ea3daa1dcb55

class Application{
    public:
        Application();
        void run();
    private:
        ColorThemeManager colorThemeManager;

        MenuState menuState;
        SLLState SLL;
        AVLState AVL;
        ShortestPathState ST;
<<<<<<< HEAD
<<<<<<< HEAD
        // HashTableVisualization hashTable(fontNumber, fontText, true, speed);
=======
        HashTableVisualization hashTable(fontNumber, fontText, true, speed);
>>>>>>> 57ca819e1282dcd2198f5aff20a8ea3daa1dcb55
=======
        HashTableVisualization hashTable(fontNumber, fontText, true, speed);
>>>>>>> 57ca819e1282dcd2198f5aff20a8ea3daa1dcb55
};

#endif