#ifndef SLLNODE_H
#define SLLNODE_H

#include <string>

#include "raylib.h"
#include "SLL/SLLArrow.h"
#include "GUI/Resources.h"
class SLLNode{
    public:
        SLLNode();
        ~SLLNode();

        void setValue(int value);
        void setPosition(Vector2 position);
        void setNull();

        Vector2 getStartPos();
        Vector2 getEndPos();
        Vector2 getPosition();
        int getValue();
        
        void updateCur(Vector2 targetPos);
        void drawCur();
        
    private:
        Rectangle node;
        int value;
        SLLArrow* Pointer;

        Vector2 position;
};

#endif