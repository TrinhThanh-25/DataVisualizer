// #include "Tree234Visual.h"
// #include <string>

// Tree234Visual::Tree234Visual(Font font) : font(font) {
//     root = nullptr;
//     speed = 0.05f;
//     std::vector<std::vector<TreeNode*>> history;
//     int presIndex = 0, stateIndex = 0;
//     treePresentation = new TreePresentation(font, font, speed, root, history, presIndex, stateIndex);
//     showInputBox = false;
//     inputText = "";
//     inputNumber = 0;
//     insertButton = {20, 20, 100, 40};
// }

// Tree234Visual::~Tree234Visual() {
//     delete treePresentation;
//     // TODO: Thêm logic để delete toàn bộ cây (root)
// }

// void Tree234Visual::Update() {
//     Vector2 mousePos = GetMousePosition();
//     bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

//     treePresentation->DrawPresentation();

//     if (CheckCollisionPointRec(mousePos, insertButton) && mousePressed) {
//         showInputBox = true;
//         inputText = "";
//     }

//     if (showInputBox) {
//         int key = GetCharPressed();
//         while (key > 0) {
//             if ((key >= 48 && key <= 57) && inputText.length() < 10) {
//                 inputText += (char)key;
//             }
//             key = GetCharPressed();
//         }

//         if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()) {
//             inputText.pop_back();
//         }

//         if (IsKeyPressed(KEY_ENTER) && !inputText.empty()) {
//             inputNumber = std::stoi(inputText);
//             Insert(inputNumber);
//             showInputBox = false;
//             inputText = "";
//         }

//         if (IsKeyPressed(KEY_ESCAPE)) {
//             showInputBox = false;
//             inputText = "";
//         }
//     }
// }

// void Tree234Visual::Draw() {
//     DrawRectangleRec(insertButton, GRAY);
//     DrawText("Insert", insertButton.x + 20, insertButton.y + 10, 20, WHITE);

//     if (showInputBox) {
//         Rectangle inputBox = {200, 200, 200, 40};
//         DrawRectangleRec(inputBox, LIGHTGRAY);
//         DrawText(inputText.c_str(), inputBox.x + 10, inputBox.y + 10, 20, BLACK);
//         DrawText("Press Enter to confirm, Esc to cancel", inputBox.x, inputBox.y + 50, 20, DARKGRAY);
//     }

//     DrawTree(root);
// }

// void Tree234Visual::DrawTree(TreeNode* root) {
//     if (root) {
//         root->DrawNode();
//         root->DrawLinktoChild();
//         for (TreeNode* child : root->children) {
//             DrawTree(child);
//         }
//     }
// }

// void Tree234Visual::Insert(int key) {
//     treePresentation->InsertKeyOperation(key);
//     root = treePresentation->tree;
// }