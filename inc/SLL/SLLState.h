#ifndef SLLSTATE_H
#define SLLSTATE_H

#include <sstream>
#include <vector>
#include <random>

#include "SLL/SLLCode.h"
#include "SLL/SinglyLinkedList.h"
#include "SLL/SLLPanel.h"
#include "GUI/CodeBlock.h"
#include "GUI/inputBox.h"
#include "GUI/Button.h"

class SLLState{
    public:
        SLLState();
        void update();
        void draw();
        
        void resetBox();
        std::string getRandomInput();
        bool isBackPressed();

    private:
        SinglyLinkedList SLL;
        CodeBlock SLLCode;
        SLLPanel panel;

        InputBox createBox;
        InputBox indexBox;
        InputBox valueBox;

        Button Random;
        Button LoadFile;
        Button Apply;
        Button Front;
        Button End;
};

#endif