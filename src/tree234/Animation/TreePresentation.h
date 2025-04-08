// #pragma once
// #include "SetofOperation.h"
// #include "../TreeNode.h"

// class TreePresentation {
// public:
//     Font fontNumber, fontText;
//     float& speed;
//     TreeNode* tree;
//     std::vector<SetofOperation> SetOperations;
//     int currentStep;
//     std::vector<std::vector<TreeNode*>>& historyState;
//     int& currentPresentationIndex;
//     int& currentStateIndex;

//     TreePresentation(Font fontNumber, Font fontText, float& speed, TreeNode* tree, 
//                      std::vector<std::vector<TreeNode*>>& historyState, 
//                      int& currentPresentationIndex, int& currentStateIndex);
//     void InsertKeyOperation(int key);
//     bool DrawPresentation();
//     void clear();
// };