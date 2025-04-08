// #include "Operation.h"

// Operation::Operation(Font fontNumber, Font fontText, float& speed, TreeNode* node) 
//     : fontNumber(fontNumber), fontText(fontText), speed(speed), node(node) {
//     curAnimation = 0.0f;
//     type = NORMAL;
// }

// bool Operation::DrawNormalNode() {
//     if (!node) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         node->currentColor = node->colorNormal;
//         return false;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::DrawChosenNode() {
//     if (!node) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         node->currentColor = node->colorChosen;
//         return false;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::DrawInsertEdge() {
//     if (!node || node->children.empty()) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         for (int i = 0; i < node->children.size(); i++) {
//             node->arrowPos[i] = {node->position.x + (node->children[i]->position.x - node->position.x) * curAnimation, 
//                                  node->position.y + (node->children[i]->position.y - node->position.y) * curAnimation};
//         }
//         return false;
//     }
//     for (int i = 0; i < node->children.size(); i++) {
//         node->arrowPos[i] = node->children[i]->position;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::SplitNode() {
//     if (!node || node->keys.size() < 3) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         int midKey = node->keys[1];
//         TreeNode* left = new TreeNode({node->keys[0]}, {}, {0, 0}); // Tọa độ tạm, sẽ được LayoutTree cập nhật
//         TreeNode* right = new TreeNode({node->keys[2]}, {}, {0, 0});

//         if (!node->isLeaf && node->children.size() == 4) {
//             left->children = {node->children[0], node->children[1]};
//             right->children = {node->children[2], node->children[3]};
//             left->isLeaf = false;
//             right->isLeaf = false;
//             for (TreeNode* child : left->children) if (child) child->parent = left;
//             for (TreeNode* child : right->children) if (child) child->parent = right;
//         } else {
//             left->isLeaf = true;
//             right->isLeaf = true;
//         }

//         left->parent = node;
//         right->parent = node;

//         node->keys = {midKey};
//         node->children = {left, right};
//         node->isLeaf = false;
//         node->size = {50, 50};

//         TreeNode* root = node;
//         while (root->parent) root = root->parent;
//         root->LayoutTree(0, 800, 0, 100);
//         curAnimation = 0.0f;
//         return true;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::MergeKeyToParent() {
//     if (!node || !node->parent || node->keys.size() != 1 || node->children.size() != 2) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         int keyToMerge = node->keys[0];
//         TreeNode* parent = node->parent;

//         int i = 0;
//         for (; i < parent->keys.size(); i++) {
//             if (keyToMerge < parent->keys[i]) break;
//         }

//         parent->keys.insert(parent->keys.begin() + i, keyToMerge);
//         parent->children[i] = node->children[0];
//         parent->children.insert(parent->children.begin() + i + 1, node->children[1]);

//         if (node->children[0]) node->children[0]->parent = parent;
//         if (node->children[1]) node->children[1]->parent = parent;

//         for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
//             if (*it == node) {
//                 parent->children.erase(it);
//                 break;
//             }
//         }

//         node->keys.clear();
//         node->children.clear();

//         switch (parent->keys.size()) {
//             case 1: parent->size = {50, 50}; break;
//             case 2: parent->size = {100, 50}; break;
//             case 3: parent->size = {150, 50}; break;
//         }

//         TreeNode* root = parent;
//         while (root->parent) root = root->parent;
//         root->LayoutTree(0, 800, 0, 100);
//         curAnimation = 0.0f;
//         return true;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::InsertToLeaf() {
//     if (!node || !node->isLeaf) return true;
//     if (curAnimation < 1.0f) {
//         curAnimation += speed;
//         for (int k : node->keys) {
//             if (k == key) return false;
//         }
//         int i = 0;
//         for (; i < node->keys.size(); i++) {
//             if (key < node->keys[i]) break;
//         }
//         if (i == node->keys.size()) node->keys.push_back(key);
//         else node->keys.insert(node->keys.begin() + i, key);
//         switch (node->keys.size()) {
//             case 1: node->size = {50, 50}; break;
//             case 2: node->size = {100, 50}; break;
//             case 3: node->size = {150, 50}; break;
//         }

//         TreeNode* root = node;
//         while (root->parent) root = root->parent;
//         root->LayoutTree(0, 800, 0, 100);
//         curAnimation = 0.0f;
//         return true;
//     }
//     curAnimation = 0.0f;
//     return true;
// }

// bool Operation::DrawOperation() {
//     if (!node) return true;
//     switch (type) {
//         case NORMAL: return DrawNormalNode();
//         case HIGHLIGHT: return DrawChosenNode();
//         case INSERT_EDGE: return DrawInsertEdge();
//         case SPLIT_NODE: return SplitNode();
//         case MERGE_KEY_TO_PARENT: return MergeKeyToParent();
//         case INSERT_TO_LEAF: return InsertToLeaf();
//         default: return true;
//     }
// }