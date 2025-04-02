#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"

class Node{
    public:
        int data;
        Node * next;
        Vector2 position;
        Vector2 finalPosition;
        Vector2 arrowPos;
        Vector2 size;
        Color colorNormal, colorChosen, colorCurrent;
        bool isChosen = false;
        Node(int data, Vector2 position, Vector2 size, Color colorNormal, Color colorChosen) {
            this->data = data;
            this->position = position;
            this->finalPosition = position;
            this->arrowPos = position;
            this->size = size;
            this->colorNormal = colorNormal;
            this->colorCurrent = colorNormal;
            this->colorChosen = colorChosen;
            this->next = NULL;
            this->isChosen = false;    
        }
        Node(int data){
            this->data = data;
            this->next = NULL;
        }
};