#pragma once

#include "raylib.h"

class Button{
    public:
        Button();
        void setTexture(const char* path);
        void setPosition(int posX, int poxY);
        void setSize(int width, int height);
        void setText(const char* text, int fontSize);
        void setRectangle();
        void update();
        
        void drawRectangle(int width, int height);
        void drawRectangleRounded(int roundness);
        void drawRectangleRoundedLinesEx(int roundness, int segments, int lineThick, Color color);
        
        void drawTexture(Vector2 position);
        void drawText(Color color);

        Vector2 getSize();
        int getfontSize();
        Vector2 getPosition();

        bool isPressed();
        bool isHovered();
        void Selected();
        void deSelected();

    private:
        Rectangle rectangle;
        Color color;
        Texture2D texture;
        Vector2 position;
        Vector2 size;
        bool isSeclected = false;
        const char* text;
        int fontSize;
};
