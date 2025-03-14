#include "HashTable/HashTable.h"

HashTable::HashTable() : table(TABLE_SIZE), animationKey(-1), animationIndex(-1), isAnimating(false), found(false),
    inputBox(50, 20, 200, 40, 10, DARKGRAY, WHITE) {
    
    insertButton.setPosition({300, 20});
    insertButton.setSize({100, 40});
    insertButton.setText("Insert", 20);
    insertButton.setColor(GRAY, LIGHTGRAY, DARKGRAY);

    deleteButton.setPosition({420, 20});
    deleteButton.setSize({100, 40});
    deleteButton.setText("Delete", 20);
    deleteButton.setColor(RED, MAROON, DARKGRAY);

    findButton.setPosition({540, 20});
    findButton.setSize({100, 40});
    findButton.setText("Find", 20);
    findButton.setColor(GREEN, DARKGREEN, DARKGRAY);
}

int HashTable::HashFunction(int key) {
    return key % TABLE_SIZE;
}

void HashTable::Insert(int key) {
    animationKey = key;
    animationIndex = HashFunction(key);
    isAnimating = true;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay for animation
    float startX = animationIndex * CELL_WIDTH + 10;
    float startY = 100 + table[animationIndex].size() * (CELL_HEIGHT + 5);
    table[animationIndex].push_back(Node(key, startX, startY, GREEN));
    isAnimating = false;
    animationKey = -1;
}

void HashTable::Delete(int key) {
    int index = HashFunction(key);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == key) {
            table[index].erase(it);
            break;
        }
    }
}

bool HashTable::Find(int key) {
    int index = HashFunction(key);
    for (auto &node : table[index]) {
        if (node.key == key) {
            node.color = YELLOW;
            return true;
        }
    }
    return false;
}

void HashTable::DrawTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        DrawRectangleLines(i * CELL_WIDTH, 50, CELL_WIDTH, CELL_HEIGHT, WHITE);
        DrawText(TextFormat("%d", i), i * CELL_WIDTH + 10, 60, 20, WHITE);
        float yOffset = 100;
        for (auto &node : table[i]) {
            DrawRectangle(node.x, node.y, CELL_WIDTH - 20, CELL_HEIGHT - 10, node.color);
            DrawText(TextFormat("%d", node.key), node.x + 10, node.y + 10, 20, BLACK);
            yOffset += CELL_HEIGHT + 5;
        }
    }
    if (isAnimating && animationKey != -1) {
        DrawText(TextFormat("%d %% %d = %d", animationKey, TABLE_SIZE, animationIndex), SCREEN_WIDTH - 200, 200, 20, RED);
    }
}

void HashTable::HandleInput() {
    inputBox.Update();
    insertButton.update();
    deleteButton.update();
    findButton.update();

    if (insertButton.isPressed() && inputBox.GetText() != "") {
        int inputKey = std::stoi(inputBox.GetText());
        std::thread insertThread(&HashTable::Insert, this, inputKey);
        insertThread.detach();
        inputBox = InputBox(50, 20, 200, 40, 10, DARKGRAY, WHITE); // Reset InputBox
    }

    if (deleteButton.isPressed() && inputBox.GetText() != "") {
        int inputKey = std::stoi(inputBox.GetText());
        Delete(inputKey);
        inputBox = InputBox(50, 20, 200, 40, 10, DARKGRAY, WHITE); // Reset InputBox
    }

    if (findButton.isPressed() && inputBox.GetText() != "") {
        int inputKey = std::stoi(inputBox.GetText());
        found = Find(inputKey);
        inputBox = InputBox(50, 20, 200, 40, 10, DARKGRAY, WHITE); // Reset InputBox
    }
}

void HashTable::DrawUI() {
    inputBox.Draw();
    insertButton.drawRectangle(insertButton.getSize());
    deleteButton.drawRectangle(deleteButton.getSize());
    findButton.drawRectangle(findButton.getSize());

    insertButton.drawText(WHITE);
    deleteButton.drawText(WHITE);
    findButton.drawText(WHITE);
}

void HashTable::Run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hash Table Chaining Visualization with Buttons");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        HandleInput();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTable();
        DrawUI();
        EndDrawing();
    }

    CloseWindow();
}

