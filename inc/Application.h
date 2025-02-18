#pragma once

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