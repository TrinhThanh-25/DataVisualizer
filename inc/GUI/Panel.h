#ifndef PANEL_H
#define PANEL_H

#include "GUI/Button.h"
#include "GUI/inputBox.h"

class Panel{
    public:
        Panel();
        void draw();
        void update();
        bool isBackPressed();
        bool isAnyButtonPressed();

        bool isCreateUsed();
        bool isAddUsed();
        bool isRemoveUsed();
        bool isSearchUsed();
        bool isUpdateUsed();
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
        Button* isUsing=nullptr;
};

#endif