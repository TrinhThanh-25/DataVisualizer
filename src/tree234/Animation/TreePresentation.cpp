// #include "TreePresentation.h"

// TreePresentation::TreePresentation(Font fontNumber, Font fontText, float& speed, TreeNode* tree, 
//                                   std::vector<std::vector<TreeNode*>>& historyState, 
//                                   int& currentPresentationIndex, int& currentStateIndex) 
//     : fontNumber(fontNumber), fontText(fontText), speed(speed), tree(tree), 
//       historyState(historyState), currentPresentationIndex(currentPresentationIndex), 
//       currentStateIndex(currentStateIndex), currentStep(0) {}

// void TreePresentation::InsertKeyOperation(int key) {
//     if (!tree) {
//         tree = new TreeNode({key}, {}, {400, 50});
//         tree->LayoutTree(0, 800, 0, 100);
//         SetofOperation setInit(fontNumber, fontText, speed);
//         Operation init(fontNumber, fontText, speed, tree);
//         init.type = Operation::INSERT_TO_LEAF;
//         init.SetKey(key);
//         setInit.AddOperation(init);
//         SetOperations.push_back(setInit);
//         historyState.push_back({tree});
//         return;
//     }

//     TreeNode* node = tree;

//     while (true) {
//         SetofOperation setHighlight(fontNumber, fontText, speed);
//         Operation highlight(fontNumber, fontText, speed, node);
//         highlight.type = Operation::HIGHLIGHT;
//         setHighlight.AddOperation(highlight);
//         SetOperations.push_back(setHighlight);

//         SetofOperation setNormal(fontNumber, fontText, speed);
//         Operation normal(fontNumber, fontText, speed, node);
//         normal.type = Operation::NORMAL;
//         setNormal.AddOperation(normal);
//         SetOperations.push_back(setNormal);

//         if (node->keys.size() == 3) {
//             SetofOperation setSplit(fontNumber, fontText, speed);
//             Operation split(fontNumber, fontText, speed, node);
//             split.type = Operation::SPLIT_NODE;
//             setSplit.AddOperation(split);
//             SetOperations.push_back(setSplit);

//             if (node->parent) {
//                 SetofOperation setMerge(fontNumber, fontText, speed);
//                 Operation merge(fontNumber, fontText, speed, node);
//                 merge.type = Operation::MERGE_KEY_TO_PARENT;
//                 setMerge.AddOperation(merge);
//                 SetOperations.push_back(setMerge);
//             } else {
//                 TreeNode* newRoot = new TreeNode({}, {}, {400, 50});
//                 newRoot->children.push_back(node);
//                 node->parent = newRoot;
//                 tree = newRoot;

//                 SetofOperation setMerge(fontNumber, fontText, speed);
//                 Operation merge(fontNumber, fontText, speed, node);
//                 merge.type = Operation::MERGE_KEY_TO_PARENT;
//                 setMerge.AddOperation(merge);
//                 SetOperations.push_back(setMerge);
//             }
//         }

//         if (node->isLeaf) {
//             SetofOperation setInsert(fontNumber, fontText, speed);
//             Operation insert(fontNumber, fontText, speed, node);
//             insert.type = Operation::INSERT_TO_LEAF;
//             insert.SetKey(key);
//             setInsert.AddOperation(insert);
//             SetOperations.push_back(setInsert);
//             break;
//         }

//         int i = 0;
//         for (; i < node->keys.size(); i++) {
//             if (key < node->keys[i]) break;
//         }
//         node = node->children[i];
//     }

//     historyState.push_back({tree});
// }

// bool TreePresentation::DrawPresentation() {
//     if (SetOperations.empty() || currentStep >= SetOperations.size()) return true;
//     return SetOperations[currentStep].Draw() && ++currentStep >= SetOperations.size();
// }

// void TreePresentation::clear() {
//     SetOperations.clear();
//     currentStep = 0;
// }