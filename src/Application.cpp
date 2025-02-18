#include "Application.h"

Application::Application() : menuState(MenuState()) {
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
}

void Application::run(){
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
        }
        EndDrawing();
    }
    CloseWindow();
}