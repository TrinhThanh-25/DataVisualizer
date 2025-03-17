// InputBox.h
#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "raylib.h"
#include <string>

class InputBox {
private:
    Rectangle box;
    std::string text;
    int maxLength;
    bool isActive;
    Color boxColor;
    Color textColor;
    float blinkTimer;
    bool showCursor;
    bool isMouseonBox;

public:
    InputBox(float x, float y, float width, float height, int maxLen, Color boxCol, Color txtCol);
    void Update();
    void Draw();
    std::string GetText() const;
    void resetBox();
    void setText(std::string text);
    void clearBox();

    void setPosition(Vector2 position);
};

#endif