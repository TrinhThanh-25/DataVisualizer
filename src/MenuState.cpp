#include "MenuState.h"

MenuState::MenuState(){
    this->background = LoadTexture("button.png");
    this->title = "Data Structure Visualization";

    this->exit.setText("Exit",menuButtonFontSize);
    this->exit.setSize({70,50});
    this->exit.setPosition({1500,800});
    this->exit.setColor(menuNormal,menuHovered,menuPressed);
    this->exit.setRectangle();

    this->SLL.setText("Singly Linked List",menuButtonFontSize);
    this->SLL.setSize(menuButtonSize);
    this->SLL.setPosition({400,550});
    this->SLL.setColor(menuNormal,menuHovered,menuPressed);
    this->SLL.setRectangle();
    
    this->LinearHT.setText("Linear Hashing Table",menuButtonFontSize);
    this->LinearHT.setSize(menuButtonSize);
    this->LinearHT.setPosition({800 ,550});
    this->LinearHT.setColor(menuNormal,menuHovered,menuPressed);
    this->LinearHT.setRectangle();

    this->Tree234.setText("2-3-4 Tree",menuButtonFontSize);
    this->Tree234.setSize(menuButtonSize);
    this->Tree234.setPosition({1200 ,550});
    this->Tree234.setColor(menuNormal,menuHovered,menuPressed);
    this->Tree234.setRectangle();

    this->AVLTree.setText("AVL Tree",menuButtonFontSize);
    this->AVLTree.setSize(menuButtonSize);
    this->AVLTree.setPosition({400 ,700});
    this->AVLTree.setColor(menuNormal,menuHovered,menuPressed);
    this->AVLTree.setRectangle();

    this->MinSpanningTree.setText("Minimum Spanning Tree",menuButtonFontSize);
    this->MinSpanningTree.setSize(menuButtonSize);
    this->MinSpanningTree.setPosition({800, 700});
    this->MinSpanningTree.setColor(menuNormal,menuHovered,menuPressed);
    this->MinSpanningTree.setRectangle();

    this->ShortestPath.setText("Shortest Path",menuButtonFontSize);
    this->ShortestPath.setSize(menuButtonSize);
    this->ShortestPath.setPosition({1200 ,700});
    this->ShortestPath.setColor(menuNormal,menuHovered,menuPressed);
    this->ShortestPath.setRectangle();
}

void MenuState::draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawText(this->title, 800 - MeasureText(this->title, 40)/2, 350, 40, BLACK);

    this->exit.drawRectangleRounded(70);
    this->SLL.drawRectangleRounded(70);
    this->LinearHT.drawRectangleRounded(70);
    this->Tree234.drawRectangleRounded(70);
    this->AVLTree.drawRectangleRounded(70);
    this->MinSpanningTree.drawRectangleRounded(70);
    this->ShortestPath.drawRectangleRounded(70);

    this->exit.drawText(BLACK);
    this->SLL.drawText(BLACK);
    this->LinearHT.drawText(BLACK);
    this->Tree234.drawText(BLACK);
    this->AVLTree.drawText(BLACK);
    this->MinSpanningTree.drawText(BLACK);
    this->ShortestPath.drawText(BLACK);
}

void MenuState::update(){
    if(this->exit.isPressed()){
        CloseWindow();
    }
    if(this->SLL.isPressed()){
        this->isSLL = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isSLL){
            *isUsed=false;
        }
        isUsed=&isSLL;
    }
    else if(this->LinearHT.isPressed()){
        this->isLinearHT = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isLinearHT){
            *isUsed=false;
        }
        isUsed=&isLinearHT;
    }
    else if(this->Tree234.isPressed()){
        this->isTree234 = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isTree234){
            *isUsed=false;
        }
        isUsed=&isTree234;
    }
    else if(this->AVLTree.isPressed()){
        this->isAVLTree = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isAVLTree){
            *isUsed=false;
        }
        isUsed=&isAVLTree;
    }
    else if(this->MinSpanningTree.isPressed()){
        this->isMinSpanningTree = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isMinSpanningTree){
            *isUsed=false;
        }
        isUsed=&isMinSpanningTree;
    }
    else if(this->ShortestPath.isPressed()){
        this->isShortestPath = true;
        this->isStarted = true;
        if(this->isUsed&&isUsed!=&isShortestPath){
            *isUsed=false;
        }
        isUsed=&isShortestPath;
    }
    this->exit.update();
    this->SLL.update();
    this->LinearHT.update();
    this->Tree234.update();
    this->AVLTree.update();
    this->MinSpanningTree.update();
    this->ShortestPath.update();
}