#include "Application.h"

Application::Application(){}

void Application::run(){
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(!this->menuState.isStarted){
            this->menuState.update();
            this->menuState.draw();
        }
        else if(this->menuState.isSLL){
            this->SLL.update();
            this->SLL.draw();
        }
        else if(this->menuState.isAVLTree){
            this->AVL.update();
            this->AVL.draw();
        }
        else if(this->menuState.isShortestPath){
            this->ST.update();
            this->ST.draw();
        }
        else{
            this->panel.update();
            this->panel.draw();   
        }
        if(this->panel.isBackPressed()){
            this->menuState.isStarted=false;
        }
        EndDrawing();
    }
    CloseWindow();
}