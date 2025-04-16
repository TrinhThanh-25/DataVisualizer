#pragma once
#include "raylib.h"
#include "Animation/TreePresentation.h"
#include <vector>
#include <iostream>
#include "TreeNode.h"
#include "animation/InputPanel.h"
#include "../GUI/Slider.h"
#include "../GUI/PlayBackControl.h"

class Tree234Visual {
public:
    TreeNode* root;
    TreePresentation treePresentation;
    Font font;
    float &speed;
    bool showInputBox;
    std::string inputText;
    int inputNumber;
    Rectangle insertButton;
    InputPanel inputPanel;

    std::vector<std::vector<TreeNode*>> historyState;
    int currentPresentationIndex;
    int currentStateIndex;

    Slider speedSlider;
    bool isRewinding;

    PlaybackControl playbackControl;

    Tree234Visual(float & speed);
    ~Tree234Visual();
    
    void Update();
    void Draw();
    void DrawTree(TreeNode* root);
    void Insert(int key);
};