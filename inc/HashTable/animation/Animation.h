#pragma once
#include "raylib.h"
#include "../Node.h"
#include "GUI/CodeBlock.h"

class Animation {
public:
    float& speed;
    Vector2 target;
    int type;
    float curAnimation;
    Node* node;
    int code = 0;

    CodeBlock & codeBlock;

    Animation(float &speed, Node* node, CodeBlock & codeBlock);
    Animation(float &speed, Node* node, Vector2 target, CodeBlock & codeBlock);

    bool DrawChosenNode();
    bool DrawNormalNode();
    bool DrawFadeInNode(); // Không cần Presentation vì không dùng pendingFadeInNode
    bool DrawFadeOutNode();
    bool DrawMoveNodeAnimation();
    bool DrawInsertEdgeAnimation();
    bool DrawDeleteEdgeAnimation();
    bool SetCode();
    bool DrawAnimation();
};