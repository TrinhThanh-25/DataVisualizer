#ifndef SLLNODE_H
#define SLLNODE_H

#include "SLL/SLLArrow.h"
#include "GUI/Resources.h"

class SLLNode{
    public:
        SLLNode();
        ~SLLNode();

        void setNull();
        void setValue(int value);
        void setPosition(Vector2 position);
        void setTarget(Vector2 targetPos);
        void setTargetPosition(Vector2 targetPos);
        void setDestination(Vector2 targetPos);

        Vector2 getStartPos();
        Vector2 getEndPos();
        Vector2 getPosition();
        int getValue();
        
        void updateNode();
        void updateCur();
        void drawCur();
        
    private:
        Rectangle node;
        int value;
        SLLArrow* Pointer;

        Color nodeColor;
        Color textColor;

        Vector2 position;
        Vector2 targetPosition;
};

#endif