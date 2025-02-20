#ifndef SLLNODE_H
#define SLLNODE_H

#include <string>

#include "raylib.h"
#include "SLL/SLLArrow.h"
class SLLNode{
    public:
        SLLNode();

        void setValue(int value);
        void setPosition(float posX, float posY);
        void setSize(float width, float height);

        Vector2 getStartPos();
        Vector2 getEndPos();
        
        void updateCur();
        void drawCur();
        
    private:
        Rectangle node;
        int value;
        std::string text;
        SLLArrow* Pointer;
        Vector2 startPos;
        Vector2 endPos;
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
