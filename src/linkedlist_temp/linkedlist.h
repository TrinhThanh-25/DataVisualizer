// LinkedListVisualizer.h
#ifndef LINKEDLISTVISUALIZER_H
#define LINKEDLISTVISUALIZER_H

#include "raylib.h"
#include <vector>
#include <string>
#include <cmath>

class LinkedListVisualizer {
private:
    struct Node {
        int value;
        float x, y;
        float targetX;
    };
    
    std::vector<Node> linkedList;
    bool inLinkedListScreen = false;
    bool isTypingValue = false;
    bool isTypingPosition = false;
    char inputBuffer[10] = "";
    char positionBuffer[10] = "";
    int inputIndex = 0;
    int positionIndex = 0;
    
public:
    void Run();
    
private:
    void DrawHomeScreen();
    void DrawLinkedListScreen();
    void InsertNode(int value, int position);
    void DeleteNode(int position);
    void AnimateNodes();
};

#endif // LINKEDLISTVISUALIZER_H