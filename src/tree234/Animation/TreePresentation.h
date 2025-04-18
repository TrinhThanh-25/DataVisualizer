#pragma once
#include "SetofOperation.h"
#include "../TreeNode.h"
#include <iostream>

class TreePresentation {
public:
    Font fontNumber, fontText;
    float& speed;
    TreeNode*& tree;
    TreeNode* current; // Changed from TreeNode*& current = tree;
    std::vector<SetofOperation> SetOperations;
    int currentStep;
    std::vector<std::vector<TreeNode*>>& historyState;
    int& currentPresentationIndex;
    int& currentStateIndex;
    bool isFinished = false;

    bool isSplit = false;

    TreePresentation(Font fontNumber, Font fontText, float& speed, TreeNode*& tree,
                     std::vector<std::vector<TreeNode*>>& historyState, 
                     int& currentPresentationIndex, int& currentStateIndex);

   // ~TreePresentation();
    void InsertKeyOperation(int key);
    void FindKeyOperation(int key);
    void DeleteKeyOperation(int key);
    void CreateTree(int numofKey);
    bool DrawPresentation();
    void clear();
};