#ifndef AVLSTATE_H
#define AVLSTATE_H

#include "AVL/AVLCode.h"
#include "AVL/AVL.h"
#include "GUI/Panel.h"
#include "GUI/CodeBlock.h"
#include "GUI/inputBox.h"
#include "GUI/Button.h"

#include <sstream>
#include <vector>
#include <random>

class AVLState {   
    public: 
        AVLState();
        void update();
        void draw();

        void resetBox();
        std::string getRandomInput();
        
    private:
        AVL AVL;
        CodeBlock AVLCode;
        Panel panel;
        
        InputBox createBox;
        InputBox valueBox;

        Button Random;
        Button LoadFile;
        Button Apply;
};

#endif