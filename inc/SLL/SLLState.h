#ifndef SLLSTATE_H
#define SLLSTATE_H

#include "SLL/SLLCode.h"
#include "SLL/SinglyLinkedList.h"
#include "GUI/Panel.h"
#include "GUI/CodeBlock.h"
#include "GUI/inputBox.h"
#include "GUI/Button.h"

#include <sstream>
#include <vector>
#include <random>
class SLLState{
    public:
        SLLState();
        void update();
        void draw();
        
        void resetBox();
        std::string getRandomInput();

    private:
        SinglyLinkedList SLL;
        CodeBlock SLLCode;
        Panel panel;

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