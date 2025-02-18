#pragma once

#include "raylib.h"
#include "GUI/Resources.h"

class Button{
    public:
        Button();
        void setTexture(const char* path);
        void setPosition(int posX, int posY);
        void setSize(int width, int height);
        void setText(const char* text, int fontSize);
        void setRectangle();
        void setColor(Color normal, Color hovered, Color pressed);
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
        Color normal;
        Color hovered;
        Color pressed;
        Texture2D texture;
        Vector2 position;
        Vector2 size;
        bool isSelected = false;
        const char* text;
        int fontSize=0;
};
