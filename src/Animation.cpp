#include "../inc/HashTable/animation/Animation.h"

Animation::Animation(Font fontNumber, Font fontText, float speed, Node* node)
    : fontNumber(fontNumber), fontText(fontText), speed(speed), node(node), curAnimation(0.0f), type(0) {}

Animation::Animation(Font fontNumber, Font fontText, float speed, Node* node, Vector2 target)
    : fontNumber(fontNumber), fontText(fontText), speed(speed), node(node), target(target), curAnimation(0.0f), type(0) {}

bool Animation::DrawChosenNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->colorCurrent = node->colorChosen;
        node->isChosen = true;
        return false;
    }
    node->colorCurrent = node->colorNormal;
    node->isChosen = false;
    curAnimation = 0.0f;
    return true;
}

bool Animation::DrawFadeInNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->colorCurrent = Fade(node->colorNormal, curAnimation);
        return false;
    }
    node->colorCurrent = node->colorNormal;
    return true;
}

bool Animation::DrawFadeOutNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->colorCurrent = Fade(node->colorNormal, 1.0f - curAnimation);
        return false;
    }
    return true;
}

bool Animation::DrawMoveNodeAnimation() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->position.x = node->position.x * (1.0f - curAnimation) + target.x * curAnimation;
        node->position.y = node->position.y * (1.0f - curAnimation) + target.y * curAnimation;
        return false;
    }
    node->position = target;
    node->finalPosition = target;
    curAnimation = 0.0f;
    return true;
}

bool Animation::DrawInsertEdgeAnimation() {
    if (!node || !node->next) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        Vector2 arrowPos = {node->position.x + (node->next->position.x - node->position.x) * curAnimation,
                           node->position.y + (node->next->position.y - node->position.y) * curAnimation};
        DrawLineEx(node->position, arrowPos, 2, BLACK);
        return false;
    }
    return true;
}

bool Animation::DrawDeleteEdgeAnimation() {
    if (!node || !node->next) return true;
    if (curAnimation > 0.0f) {
        curAnimation -= speed;
        Vector2 arrowPos = {node->position.x + (node->next->position.x - node->position.x) * curAnimation,
                           node->position.y + (node->next->position.y - node->position.y) * curAnimation};
        DrawLineEx(node->position, arrowPos, 2, BLACK);
        return false;
    }
    return true;
}

bool Animation::DrawAnimation() {
    if (!node) return true;
    switch (type) {
        case 1: return DrawChosenNode();
        case 2: return DrawFadeInNode();
        case 3: return DrawFadeOutNode();
        case 4: return DrawMoveNodeAnimation();
        case 6: return DrawInsertEdgeAnimation();
        case 7: return DrawDeleteEdgeAnimation();
        default: return true;
    }
}