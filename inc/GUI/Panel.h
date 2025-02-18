#pragma once

#include "GUI/Button.h"

class Panel{
    public:
        Panel();
        void draw();
        void update();
        bool isBackPressed();
    private:
        Rectangle dataTitle;
        Button Back;
        Texture2D backTexture;

        Rectangle panelHolder;
        Button Create;
        Button Add;
        Button Remove;
        Button Update;
        Button Search;
        Button Clear;
        Button* isUsing=nullptr;
};