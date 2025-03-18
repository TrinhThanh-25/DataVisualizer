#ifndef AVLSTATE_H
#define AVLSTATE_H

#include <random>

#include "AVL/AVLCode.h"
#include "AVL/AVL.h"
#include "AVL/AVLPanel.h"
#include "GUI/CodeBlock.h"
class AVLState {   
    public: 
        AVLState();
        void update();
        void draw();

        void resetBox();
        std::string getRandomInput();
        bool isBackPressed();
        
    private:
        AVL AVL;
        CodeBlock AVLCode;
        AVLPanel panel;
        
        InputBox createBox;
        InputBox valueBox;

        Button Random;
        Button LoadFile;
        Button Apply;
};

#endif