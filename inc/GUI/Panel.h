#pragma once

#include "GUI/Button.h"

class Panel{
    public:
        Panel();
        void draw();
        void update();
    private:
        Rectangle panelHolder;
        Button Create;
        Button Add;
        Button Remove;
        Button Update;
        Button Search;
        Button Clear;
        Button* isUsing=nullptr;
};