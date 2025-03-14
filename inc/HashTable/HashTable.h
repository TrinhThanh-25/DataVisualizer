#pragma once

#include "raylib.h"
#include "Button.h"
#include "InputBox.h"
#include <vector>
#include <list>
#include <string>
#include <thread>
#include <chrono>

#define TABLE_SIZE 10
#define CELL_WIDTH 120
#define CELL_HEIGHT 50
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

struct Node {
    int key;
    float x, y;
    Color color;
    Node(int k, float _x, float _y, Color _color) : key(k), x(_x), y(_y), color(_color) {}
};

class HashTable {
private:
    std::vector<std::list<Node>> table;
    int animationKey;
    int animationIndex;
    bool isAnimating;
    bool found;

    Button insertButton;
    Button deleteButton;
    Button findButton;
    InputBox inputBox;

public:
    HashTable();
    int HashFunction(int key);
    void Insert(int key);
    void Delete(int key);
    bool Find(int key);
    void DrawTable();
    void HandleInput();
    void DrawUI();
    void Run();  
};
