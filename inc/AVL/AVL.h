#ifndef AVL_H
#define AVL_H

#include <sstream>
#include <AVL/AVLNode.h>

class AVL{
    public:
        AVL();
        ~AVL();

        void createTree(std::string text);
        void insertNode(int value);
        void balanceTree();
        void balanceTree(AVLNode*& root);
        void rotateRight(AVLNode*& root);
        void rotateLeft(AVLNode*& root);
        void rotateRightLeft(AVLNode*& root);
        void rotateLeftRight(AVLNode*& root);
        void removeNode(int value);
        void searchNode(int value);
        void clearTree();
        void clearTree(AVLNode*& root);

        void calculateHeight();
        void calculateHeight(AVLNode* root);
        void calculateDepth();
        void calculateDepth(AVLNode* root);
        void setPosition();
        void setPosition(AVLNode* root);
        void setTargetPosition();
        void setTargetPosition(AVLNode* root);
        void resetHighlight();
        void resetHighlight(AVLNode* root);

        AVL* clone() const;
        AVLNode* clone(AVLNode* root) const;

        void update();
        void update(AVLNode* root);
        void draw();
        void draw(AVLNode* root);

        void clear();
    public:
        AVLNode* root;
        AVLNode* curNode;

        int animationStep = 0;
};

#endif