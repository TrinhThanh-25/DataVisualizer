#ifndef APPLICATION_H
#define APPLICATION_H

#include "MenuState.h"
#include "GUI/Panel.h"

class Application{
    public:
        Application();
        void run();
    private:
        MenuState menuState;
        Panel panel;
};

#endif