// LinkedListVisualizer.cpp
#include "linkedlist.h"

void LinkedListVisualizer::Run() {
    InitWindow(800, 600, "Linked List Visualization");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (inLinkedListScreen) {
            DrawLinkedListScreen();
        } else {
            DrawHomeScreen();
        }
        
        AnimateNodes();
        
        EndDrawing();
    }
    CloseWindow();
}

void LinkedListVisualizer::DrawHomeScreen() {
    DrawText("Linked List Visualization", 250, 100, 20, DARKGRAY);
    
    Rectangle button = {300, 250, 200, 50};
    DrawRectangleRec(button, LIGHTGRAY);
    DrawText("Linked List", 340, 265, 20, BLACK);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && 
        CheckCollisionPointRec(GetMousePosition(), button)) {
        inLinkedListScreen = true;
    }
}

void LinkedListVisualizer::DrawLinkedListScreen() {
    DrawText("Linked List", 350, 50, 20, DARKGRAY);
    
    Rectangle insertBtn = {200, 500, 150, 50};
    Rectangle deleteBtn = {450, 500, 150, 50};
    Rectangle homeBtn = {20, 500, 150, 50};
    Rectangle inputBox = {200, 450, 70, 40};
    Rectangle positionBox = {280, 450, 70, 40};
    
    DrawRectangleRec(insertBtn, LIGHTGRAY);
    DrawRectangleRec(deleteBtn, LIGHTGRAY);
    DrawRectangleRec(homeBtn, LIGHTGRAY);
    DrawRectangleRec(inputBox, isTypingValue ? GRAY : WHITE);
    DrawRectangleRec(positionBox, isTypingPosition ? GRAY : WHITE);
    
    DrawText("Insert", 250, 515, 20, BLACK);
    DrawText("Delete", 500, 515, 20, BLACK);
    DrawText("Home", 70, 515, 20, BLACK);
    DrawText(inputBuffer, 210, 460, 20, BLACK);
    DrawText(positionBuffer, 290, 460, 20, BLACK);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        isTypingValue = CheckCollisionPointRec(mouse, inputBox);
        isTypingPosition = CheckCollisionPointRec(mouse, positionBox);
        
        if (CheckCollisionPointRec(mouse, insertBtn) && inputIndex > 0 && positionIndex > 0) {
            int value = atoi(inputBuffer);
            int position = atoi(positionBuffer);
            InsertNode(value, position);
            inputIndex = 0;
            positionIndex = 0;
            inputBuffer[0] = '\0';
            positionBuffer[0] = '\0';
        } else if (CheckCollisionPointRec(mouse, deleteBtn) && positionIndex > 0) {
            int position = atoi(positionBuffer);
            DeleteNode(position);
            positionIndex = 0;
            positionBuffer[0] = '\0';
        } else if (CheckCollisionPointRec(mouse, homeBtn)) {
            inLinkedListScreen = false;
        }
    }
    
    int key = GetCharPressed();
    while (key > 0) {
        if (isTypingValue && inputIndex < 9 && key >= '0' && key <= '9') {
            inputBuffer[inputIndex++] = (char)key;
            inputBuffer[inputIndex] = '\0';
        } else if (isTypingPosition && positionIndex < 9 && key >= '0' && key <= '9') {
            positionBuffer[positionIndex++] = (char)key;
            positionBuffer[positionIndex] = '\0';
        }
        key = GetCharPressed();
    }
    if (isTypingValue && IsKeyPressed(KEY_BACKSPACE) && inputIndex > 0) {
        inputBuffer[--inputIndex] = '\0';
    }
    if (isTypingPosition && IsKeyPressed(KEY_BACKSPACE) && positionIndex > 0) {
        positionBuffer[--positionIndex] = '\0';
    }
    
    for (const Node& node : linkedList) {
        Rectangle rect = {node.x, 275, 50, 50};
        DrawRectangleRec(rect, BLUE);
        DrawText(TextFormat("%d", node.value), node.x + 10, 290, 20, WHITE);
    }
}

void LinkedListVisualizer::InsertNode(int value, int position) {
    if (position < 0 || position > linkedList.size()) return;
    
    float targetX = 100 + position * 60;
    linkedList.insert(linkedList.begin() + position, {value, 800, 275, targetX});
    
    for (size_t i = 0; i < linkedList.size(); ++i) {
        linkedList[i].targetX = 100 + i * 60;
    }
}

void LinkedListVisualizer::DeleteNode(int position) {
    if (position < 0 || position >= linkedList.size()) return;
    
    linkedList.erase(linkedList.begin() + position);
    
    for (size_t i = 0; i < linkedList.size(); ++i) {
        linkedList[i].targetX = 100 + i * 60;
    }
}

void LinkedListVisualizer::AnimateNodes() {
    for (Node& node : linkedList) {
        if (std::abs(node.x - node.targetX) > 1.0f) {
            node.x += (node.targetX - node.x) * 0.1f;
        } else {
            node.x = node.targetX;
        }
    }
}