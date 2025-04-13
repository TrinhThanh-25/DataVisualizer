#ifndef BUTTON_H
#define BUTTON_H

#include <GUI/Resources.h>
#include <GUI/ColorTheme.h>

class Button{
    public:
        Button();
        void setTexture(Texture2D texture);
        void setPosition(Vector2 position);
        void setSize(Vector2 size);
        void setText(const char* text, int fontSize);
        void update();
        void update(ColorTheme theme);
        
        void drawRectangle(Vector2 recSize);
        void drawRectangleRounded(int roundness);
        void drawOutlineRounded(int roundness, int segments, int lineThick);
        
        void drawTexture();
        void drawText();

        Vector2 getSize();
        int getfontSize();
        Vector2 getPosition();

        bool isPressed();
        bool isHovered();
        bool isSelected();
        void Selected();
        void deSelected();
        void setActive();
        void deActive();

    private:
        Rectangle rectangle;
        Color color;
        Color outlineColor;
        Color textColor;
        Texture2D texture;

        Vector2 position;
        Vector2 size;
        bool selected = false;
        const char* text;
        int fontSize=0;

        bool isActive=true;
};

#endif