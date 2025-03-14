// InputBox.cpp
#include "GUI/InputBox.h"

InputBox::InputBox(float x, float y, float width, float height, int maxLen, Color boxCol, Color txtCol)
    : box{x, y, width, height}, maxLength(maxLen), isActive(false), boxColor(boxCol), textColor(txtCol), blinkTimer(0), showCursor(true) {}

void InputBox::Update() {
    if (CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isActive = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isActive = false;
    }

    if(CheckCollisionPointRec(GetMousePosition(), box)){
        isMouseonBox = true;
    }
    else{
        isMouseonBox = false;
    }

    if (isActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32 && key <= 126) && text.length() < maxLength) {
                text += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
            text.pop_back();
        }
    }

    if(isMouseonBox){
        boxColor = GRAY;
    }
    else{
        boxColor = LIGHTGRAY;
    }
    
    blinkTimer += GetFrameTime();
    if (blinkTimer >= 0.5f) {
        blinkTimer = 0;
        showCursor = !showCursor;
    }
}

void InputBox::Draw() {
    DrawRectangleRec(box, isActive ? DARKGRAY : boxColor);
    DrawRectangleLinesEx(box, 2, BLACK);
    DrawText(text.c_str(), box.x + 5, box.y + box.height / 4, 20, textColor);
    
    if (isActive && showCursor) {
        DrawText("|", box.x + 5 + MeasureText(text.c_str(), 20), box.y + box.height / 4, 20, textColor);
    }
}

std::string InputBox::GetText() const {
    return text;
}

void InputBox::resetBox(){
    text="";
}

void InputBox::setText(std::string text){
    this->text=text;
}

void InputBox::setPosition(Vector2 position){
    box.x = position.x;
    box.y = position.y;
}