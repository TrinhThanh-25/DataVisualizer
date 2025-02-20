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
    InputBox(float x, float y, float width, float height, int maxLen = 20, Color boxCol = LIGHTGRAY, Color txtCol = BLACK);
    void Update();
    void Draw();
    std::string GetText() const;
};

#endif // INPUTBOX_H