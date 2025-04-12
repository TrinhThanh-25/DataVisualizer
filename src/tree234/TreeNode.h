// #ifndef TREEnode_H
// #define TREEnode_H

// #include <vector>
// #include <string>
// #include "raylib.h"
// #include "raymath.h"

// class TreeNode {
// public:
//     std::vector<int> keys;
//     std::vector<TreeNode*> children;
//     TreeNode* parent;
//     bool isLeaf;
//     Vector2 position;
//     Vector2 finalPosition;
//     std::vector<Vector2> arrowPos;
//     Vector2 size;
//     Color currentColor, colorChosen, colorNormal;

//     TreeNode(std::vector<int> keys, std::vector<TreeNode*> children, Vector2 position);
//     void DrawNode();
//     void DrawArrow(Vector2 start, Vector2 end);
//     void DrawLinktoChild();

//     float GetSubtreeWidth();
//     void LayoutTree(float startX, float width, int depth, float verticalSpacing); // Sửa depth thành int
// };

// #endif