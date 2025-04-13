// #pragma once
// #include "raylib.h"
// #include "raymath.h"
// #include "../TreeNode.h"
// #include <string>
// #include <vector>

// class Operation {
// public:
//     enum OperationType {
//         NORMAL = 1,
//         HIGHLIGHT = 2,
//         INSERT_EDGE = 3,
//         MOVE_NODE = 4,
//         SPLIT_NODE = 5,
//         MERGE_KEY_TO_PARENT = 6,
//         INSERT_TO_LEAF = 7
//     };
//     Font fontNumber, fontText;
//     float& speed;
//     TreeNode* node;
//     OperationType type; // Sửa int thành OperationType
//     float curAnimation;
//     int key;

//     Operation(Font fontNumber, Font fontText, float& speed, TreeNode* node);
//     void SetKey(int key) { this->key = key; }

//     bool DrawNormalNode();
//     bool DrawChosenNode();
//     bool DrawInsertEdge();
//     //bool DrawMoveNode();
//     bool SplitNode();
//     bool MergeKeyToParent(); // Đổi từ mergeKey2Par
//     bool InsertToLeaf();     // Đổi từ Insert2Leaf

//     bool DrawOperation();
// };