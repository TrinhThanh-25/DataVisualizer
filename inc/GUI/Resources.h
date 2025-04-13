#ifndef RESOURCES_H
#define RESOURCES_H

#include <raylib.h>
#include <GUI/ColorTheme.h>


extern int speed;
extern float delayTime;
const int defaultSpeed = 200;
const float defaultDelayTime = 0.5f;

//Font
//const Font fontNumber = LoadFontEx("../resources/Ubuntu-Bold.ttf");
//
//float tempSpeed = 0.1f;

//Menu
const int appTitleFontSize(40);
const Vector2 menuButtonSize({300,50});
const int menuButtonFontSize(20);

//Panel
const int dataTitleFontSize = 24;
const Vector2 dataTitleSize({400,50});
const Vector2 dataTitlePosition({800,15+dataTitleSize.y/2.0f});

const Vector2 panelButtonSize({80, 40});//Create, Add, Remove ...
const int panelButtonFontSize(15);

const Vector2 backSize({50,50});

//InputBox
const int inputBoxFontSize(20);
const int inputBoxNameFontSize(20);

//CodeBlock
const Rectangle codeBlockRec({1200,700,400,200});
const int codeBlockFontSize(16);
const Vector2 codePosition({codeBlockRec.x+15,codeBlockRec.y});

//ColorTheme Manager
const Vector2 themeButtonSize({80, 80});
const int themeButtonFontSize(18);

//SLL
const Vector2 SLLNodeSize({50,50});
const Vector2 SLLposition({150,250});
const int SLLNodeFontSize(24);

const Vector2 SLLBoxSize({260,40});
const int SLLBoxFontSize(20);
const int SLLButtonFontSize(15);

const int SLLLabelFontSize(16);

//AVL
const Vector2 AVLPosition({800,150});
const Vector2 AVLNodeSize({40,40});
const int AVLLeafSpace = 5;
const int AVLNodeFontSize(24);
const int AVLLevelSpace = 60;

const Vector2 AVLBoxSize({260,40});
const int AVLBoxFontSize(20);
const int AVLButtonFontSize(15);

//Shortest Path
const float centerX=800, centerY=350;
const float rangeX=1400,rangeY=500;

const Vector2 STNodeSize({40,40});
const int STNodeCostFontSize(12);
const int STNodeIDFontSize(24);

const Vector2 STBoxSize({260,40});
const int STBoxFontSize(20);
const int STButtonFontSize(15);

//Arrow
const int ArrowLength = 40;

//Controller
const Vector2 controllerButtonSize({50,50});
const Vector2 controllerPosition({800,860});
const Vector2 controllerSize({350,2*(900-controllerPosition.y)});

#endif