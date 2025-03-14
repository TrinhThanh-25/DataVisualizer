#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>
#include <algorithm>

#include "raylib.h"
#include "GUI/Resources.h"
#include "AVL/AVLArrow.h"

class AVLNode{
    public:
        AVLNode();
        ~AVLNode();

        void setValue(int value);
        void setPosition(Vector2 position);
        void setHeight(int value);
        void setDepth(int value);
        void setHighlight();
        void deHighlight();

        Vector2 getOrigin();
        int getValue();
        int getHeight();
        int getDepth();
        bool isLeaf();

        void updateHeight();

        void updateCur();
        void drawCur();
    public:
        AVLNode* left;
        AVLNode* right;
        AVLNode* parent;
    private:
        Rectangle node;

        AVLArrow* leftPointer;
        AVLArrow* rightPointer;

        Vector2 position;
        int value;
        int height=0;
        int depth=0;

        bool isHighlight=false;
};

#endif