#pragma once
#include "raylib.h"
#include "../Node.h"

class Animation {
public:
    Font fontNumber;
    Font fontText;
    float speed;
    Vector2 target;
    int type;
    float curAnimation;
    Node* node;

    Animation(Font fontNumber, Font fontText, float speed, Node* node);
    Animation(Font fontNumber, Font fontText, float speed, Node* node, Vector2 target);

    bool DrawChosenNode();
    bool DrawFadeInNode();
    bool DrawFadeOutNode();
    bool DrawMoveNodeAnimation();
    bool DrawInsertEdgeAnimation();
    bool DrawDeleteEdgeAnimation();
    bool DrawAnimation();
};