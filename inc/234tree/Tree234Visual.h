#pragma once
#include "raylib.h"
#include "Animation/TreePresentation.h"
#include <vector>
#include <iostream>
#include "TreeNode.h"
#include "234tree/animation/InputPanel.h"
#include "../GUI/Slider.h"
#include "../GUI/PlayBackControl.h"
#include "../GUI/CodeBlock.h"

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
    
    bool isPlaying = false;
    bool isDrawTree = true;
    bool isSkipBack = false;
    bool isCreate = false;

    std::vector<std::vector<TreeNode*>> historyState;
    std::vector<std::vector<int>> historyCodeBlock;
    int currentPresentationIndex;
    int currentStateIndex;

    Slider speedSlider;
    bool isRewinding;
    bool isPause = false;

    CodeBlock codeBlock;

    PlaybackControl playbackControl;

    Tree234Visual(float & speed);
    ~Tree234Visual();
    
    void Update();
    void Draw();
    void DrawTree(TreeNode* root);
    void Insert(int key);

    bool isBackPressed();
};