#include "Application.h"

Application::Application(){}

void Application::run(){
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
    srand(time(NULL));
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(SLL.isBackPressed()||AVL.isBackPressed()||ST.isBackPressed()){
            menuState.currentSelection=MenuSelection::NONE;
        }
        switch (menuState.currentSelection){
        case MenuSelection::NONE:
            this->menuState.update();
            this->menuState.draw();
            break;

        case MenuSelection::SLL:
            this->SLL.update();
            this->SLL.draw();
            break;

        case MenuSelection::LINEAR_HT:
            
<<<<<<< HEAD
<<<<<<< HEAD
        
=======
            this->hashTable.Draw();
            this->hashTable.HandleInput();
            this->hashTable.HandleMouseInput();
>>>>>>> fda38782a35f4de04ac5a663b69461d9339b5221
=======
            this->hashTable.Draw();
            this->hashTable.HandleInput();
            this->hashTable.HandleMouseInput();
>>>>>>> fda38782a35f4de04ac5a663b69461d9339b5221
            break;

        case MenuSelection::TREE_234:
            
            
            break;

        case MenuSelection::AVL_TREE:
            this->AVL.update();
            this->AVL.draw();
            break;

        case MenuSelection::MIN_SPANNING_TREE:

            
            break;

        case MenuSelection::SHORTEST_PATH:
            this->ST.update();
            this->ST.draw();
            break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow();
}