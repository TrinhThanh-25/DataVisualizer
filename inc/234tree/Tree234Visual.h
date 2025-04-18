#pragma once
#include "raylib.h"
#include "Animation/TreePresentation.h"
#include <vector>
#include <iostream>
#include "TreeNode.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "234tree/animation/InputPanel.h"
=======
#include "animation/InputPanel.h"
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
#include "234tree/animation/InputPanel.h"
>>>>>>> 50f6135 (Merge file)
=======
#include "animation/InputPanel.h"
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
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
    
    bool isPlaying = false;
    bool isDrawTree = true;

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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

    bool isBackPressed();
=======
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    

    void UpdateTheme(TreeNode * root);

<<<<<<< HEAD
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======

    bool isBackPressed();
>>>>>>> 50f6135 (Merge file)
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
};