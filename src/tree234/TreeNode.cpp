// #include "TreeNode.h"
// #include <iostream> // Thêm để debug

// TreeNode::TreeNode(std::vector<int> keys, std::vector<TreeNode*> children, Vector2 position) 
//     : keys(keys), children(children), position(position) {
//     finalPosition = position;
//     parent = nullptr;
//     switch (keys.size()) {
//         case 0: size = {0, 0}; break;
//         case 1: size = {50, 50}; break;
//         case 2: size = {100, 50}; break;
//         case 3: size = {150, 50}; break;
//     }
//     isLeaf = children.empty();
//     arrowPos.resize(3, {position.x + size.x / 2, position.y + size.y / 2});
//     colorChosen = GREEN;
//     colorNormal = BLACK;
//     currentColor = colorNormal;
// }

// void TreeNode::DrawNode() {
//     DrawRectangle(position.x, position.y, size.x, size.y, currentColor);
//     for (int i = 0; i < keys.size(); i++) {
//         DrawText(std::to_string(keys[i]).c_str(), position.x + 10 + i * 20, position.y + 10, 20, WHITE);
//     }
// }

// void TreeNode::DrawArrow(Vector2 start, Vector2 end) {
//     DrawLineEx(start, end, 2, BLACK);
//     Vector2 diff = Vector2Subtract(end, start);
//     float length = Vector2Length(diff);
//     if (length < 0.001f) return;
//     Vector2 dir = Vector2Normalize(diff);
//     float arrowSize = 10.0f;
//     Vector2 tip = end;
//     Vector2 baseLeft = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 150.0f), arrowSize));
//     Vector2 baseRight = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 210.0f), arrowSize));
//     DrawTriangle(tip, baseLeft, baseRight, BLACK);
// }

// void TreeNode::DrawLinktoChild() {
//     Vector2 parentPos = {position.x + size.x / 2, position.y + size.y / 2};
//     for (int i = 0; i < children.size(); i++) {
//         if (children[i]) {
//             Vector2 childPos = {children[i]->position.x + children[i]->size.x / 2, children[i]->position.y + children[i]->size.y / 2};
//             DrawArrow(parentPos, childPos);
//         }
//     }
// }

// float TreeNode::GetSubtreeWidth() {
//     if (isLeaf || children.empty()) {
//         return size.x + 60; // Khoảng cách tối thiểu giữa các node
//     }
//     float totalWidth = 0;
//     for (TreeNode* child : children) {
//         totalWidth += child->GetSubtreeWidth();
//     }
//     return totalWidth > size.x + 60 ? totalWidth : size.x + 60; // Đảm bảo đủ không gian
// }

// void TreeNode::LayoutTree(float startX, float width, int depth, float verticalSpacing) {
//     position.y = depth * verticalSpacing;
//     finalPosition.y = position.y;

//     if (isLeaf || children.empty()) {
//         position.x = startX + (width - size.x) / 2; // Căn giữa trong không gian được cấp
//         finalPosition.x = position.x;
//     } else {
//         float childWidth = width / children.size(); // Chia đều không gian cho các con
//         float currentX = startX;
//         for (TreeNode* child : children) {
//             child->LayoutTree(currentX, childWidth, depth + 1, verticalSpacing);
//             currentX += childWidth;
//         }
//         position.x = startX + (width - size.x) / 2; // Căn giữa node cha
//         finalPosition.x = position.x;
//     }
//     arrowPos.resize(3, {position.x + size.x / 2, position.y + size.y / 2});

//     // Debug: In tọa độ để kiểm tra
//     std::cout << "Node keys: ";
//     for (int k : keys) std::cout << k << " ";
//     std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
// }