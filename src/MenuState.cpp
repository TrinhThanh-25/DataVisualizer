#include "MenuState.h"

MenuState::MenuState(){
    this->background = LoadTexture("button.png");
    this->title = "Data Structure Visualization";

    this->exit.setText("Exit",20);
    this->exit.setSize(70,50);
    this->exit.setPosition(1500,800);
    this->exit.setRectangle();

    this->SLL.setText("Singly Linked List",20);
    this->SLL.setSize(300,50);
    this->SLL.setPosition(400,550);
    this->SLL.setRectangle();
    
    this->LinearHT.setText("Linear Hashing Table",20);
    this->LinearHT.setSize(300,50);
    this->LinearHT.setPosition(800 ,550);
    this->LinearHT.setRectangle();

    this->Tree234.setText("2-3-4 Tree",20);
    this->Tree234.setSize(300,50);
    this->Tree234.setPosition(1200 ,550);
    this->Tree234.setRectangle();

    this->RBTree.setText("Red-Black Tree",20);
    this->RBTree.setSize(300,50);
    this->RBTree.setPosition(400 ,700);
    this->RBTree.setRectangle();

    this->MinSpanningTree.setText("Minimum Spanning Tree",20);
    this->MinSpanningTree.setSize(300,50);
    this->MinSpanningTree.setPosition(800, 700);
    this->MinSpanningTree.setRectangle();

    this->ShortestPath.setText("Shortest Path",20);
    this->ShortestPath.setSize(300,50);
    this->ShortestPath.setPosition(1200 ,700);
    this->ShortestPath.setRectangle();
}

void MenuState::draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawText(this->title, 800 - MeasureText(this->title, 40)/2, 350, 40, BLACK);

    this->exit.drawRectangleRounded(0.7);
    this->SLL.drawRectangleRounded(0.7);
    this->LinearHT.drawRectangleRounded(0.7);
    this->Tree234.drawRectangleRounded(0.7);
    this->RBTree.drawRectangleRounded(0.7);
    this->MinSpanningTree.drawRectangleRounded(0.7);
    this->ShortestPath.drawRectangleRounded(0.7);

    this->exit.drawText(BLACK);
    this->SLL.drawText(BLACK);
    this->LinearHT.drawText(BLACK);
    this->Tree234.drawText(BLACK);
    this->RBTree.drawText(BLACK);
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
    }
    else if(this->LinearHT.isPressed()){
        this->isLinearHT = true;
        this->isStarted = true;
    }
    else if(this->Tree234.isPressed()){
        this->isTree234 = true;
        this->isStarted = true;
    }
    else if(this->RBTree.isPressed()){
        this->isRBTree = true;
        this->isStarted = true;
    }
    else if(this->MinSpanningTree.isPressed()){
        this->isMinSpanningTree = true;
        this->isStarted = true;
    }
    else if(this->ShortestPath.isPressed()){
        this->isShortestPath = true;
        this->isStarted = true;
    }
    this->exit.update();
    this->SLL.update();
    this->LinearHT.update();
    this->Tree234.update();
    this->RBTree.update();
    this->MinSpanningTree.update();
    this->ShortestPath.update();
}