#ifndef PANEL_H
#define PANEL_H

#include "GUI/Button.h"
#include "GUI/inputBox.h"

class Panel{
    public:
        Panel();
        virtual void draw()=0;
        virtual void update()=0;
        bool isBackPressed();
        virtual bool isAnyButtonPressed()=0;
    protected:
        Rectangle dataTitle;
        Button Back;

        Rectangle panelHolder;
};

#endif