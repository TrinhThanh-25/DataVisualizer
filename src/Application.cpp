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
        else{
            this->panel.update();
            this->panel.draw();
            this->SLL.update();
            this->SLL.draw();
            if(this->panel.isBackPressed()){
                this->menuState.isStarted=false;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}