#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

//Menu
const Color menuPressed({26,67,128,255});
const Color menuHovered({38,98,186,255});
const Color menuNormal({50,130,246,255});
const Vector2 menuButtonSize({300,50});
const int menuButtonFontSize(20);

//Panel
const Vector2 panelButtonSize({80, 40});//Create, Add, Remove ...
const int panelButtonFontSize(15);
const Color panelNormal({161,161,161,255});
const Color panelHovered({133,133,133,255});
const Color panelPressed({110,110,110,255});
const Color titleColor({185,185,185,255});
const Color highlightColor({255,253,85,255});

//SLL
const Vector2 SLLNodeSize({80,60});
const Vector2 SLLposition({150,250});

const Vector2 AVLNodeSize({40,40});
const int AVLSpace = 5;

const Vector2 STNodeSize({40,40});

const int ArrowLength = 50;

#endif