#ifndef APPLICATION_H
#define APPLICATION_H

#include "MenuState.h"
#include "GUI/Panel.h"
#include "SLL/SinglyLinkedList.h"

class Application{
    public:
        Application();
        void run();
    private:
        MenuState menuState;
        Panel panel;
        SinglyLinkedList SLL;
};

#endif