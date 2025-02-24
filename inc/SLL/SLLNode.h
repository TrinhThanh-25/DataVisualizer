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
        Rectangle getRecSize();
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

//std::unique_ptr<NodeData> dataPtr(mData);
//std::unique_ptr<Pointer> nextNodePtr(mPointer);

//attachChild(std::move(dataPtr));
//attachChild(std::move(nextNodePtr));

//float arrowEdge = thickness + 4.f;
 //   float arrowLength = sqrt(3.f) / 2.f * arrowEdge;
 //   float lineLength = sqrt(line.x * line.x + line.y * line.y);