#include <234tree/animation/TreePresentation.h>

TreePresentation::TreePresentation(float& speed, TreeNode*& tree,
                                  std::vector<std::vector<TreeNode*>>& historyState, 
                                  int& currentPresentationIndex, int& currentStateIndex) 
    : speed(speed), tree(tree),
      historyState(historyState), currentPresentationIndex(currentPresentationIndex), 
      currentStateIndex(currentStateIndex), currentStep(0) {
        this->current = this->tree;
      }      




bool TreePresentation::DrawPresentation() {
    if(SetOperations.empty() || currentStep >= SetOperations.size()) return true;

    if(SetOperations[currentStep].Draw()){
        switch (SetOperations[currentStep].operations[0].type) {
        
        case Operation::SPLIT_NODE: break;
        case Operation::MERGE_KEY_TO_PARENT: break;
        case Operation::INSERT_TO_LEAF: break;
        case Operation::REMOVE_LEAF: break;
        case Operation::CHANGE_KEY: break;
        case Operation::MERGE_TO_CHILDREN: break;
        case Operation::MOVE_TO_CHILDREN_NODE: break;
        default:
            TreeNode * temp = new TreeNode(tree);
            if(currentStep == 0){
                std::cout<<"day la lan dau"<<std::endl;
                currentPresentationIndex++;
                std::vector<TreeNode*> tempVec = {};
                tempVec.push_back(temp);
                historyState.push_back(tempVec);
                currentStateIndex = historyState.back().size() - 1;
                
            }
            else{
                historyState.back().push_back(temp);
                currentStateIndex = historyState.back().size() - 1;
            }
        }
        currentStep++;
    }
    if(currentStep >= SetOperations.size()){
        currentStep = 0;
        this->current = tree;
        std::cout<<"xong roi"<<std::endl;
        this->SetOperations.clear();
        //this->isFinished = true;
        return true;
    }
    //this->isFinished = false;
    return false;
    //return currentStep >= SetOperations.size();
}

void TreePresentation::clear() {
    SetOperations.clear();
    currentStep = 0;
    //this->isFinished = false;
}

void TreePresentation::InsertKeyOperation(int key){
    if(tree == nullptr){
        tree = new TreeNode({key}, {}, {800, 100});
        tree->isLeaf = true;
        this->current = tree;
        return;
    }

    //dem node 3
    int node3 = 0;
    int nodeNormal = 0;
    TreeNode * curr = tree;
    while(curr->isLeaf == false){
        nodeNormal++;
        if(curr->keys.size() == 3){
            node3++;
        }
        int i = 0;
        for(; i < curr->keys.size(); i++){
            if(curr->keys[i] > key) break;
        }
        curr = curr->children[i];
    }
    nodeNormal++;
    int finalNode3 = 0;
    if(curr->keys.size() == 3){
        node3++;
    }
    std::cout<<"nodeNormal: "<<nodeNormal<<std::endl;
    std::cout<<"node3: "<<node3<<std::endl;

    for(int i = 0; i < nodeNormal + node3 - 1; i++){
        
            std::cout<<"co do day choi ne nghen "<<std::endl;
            //highlight
            SetofOperation highlight(speed);
            Operation opHighlight(speed, this->current, this->tree, this->isSplit);
            opHighlight.type = Operation::HIGHLIGHT;
            opHighlight.SetKey(key);
            highlight.AddOperation(opHighlight);
            this->SetOperations.push_back(highlight);
            
            //normal
            SetofOperation normal(speed);
            Operation opNormal(speed, this->current, this->tree, this->isSplit);
            opNormal.type = Operation::NORMAL;
            opNormal.SetKey(key);
            normal.AddOperation(opNormal);
            this->SetOperations.push_back(normal);

            //split
            SetofOperation split(speed);
            Operation opSplit(speed, this->current, this->tree, this->isSplit);
            opSplit.type = Operation::SPLIT_NODE;
            opSplit.SetKey(key);
            split.AddOperation(opSplit);
            this->SetOperations.push_back(split);

            //move to finpos
            SetofOperation moveToFinPos(speed);
            Operation opMoveToFinPos(speed, this->current, this->tree, this->isSplit);
            opMoveToFinPos.type = Operation::MOVE_TO_FINPOS;
            opMoveToFinPos.SetKey(key);
            moveToFinPos.AddOperation(opMoveToFinPos);
            this->SetOperations.push_back(moveToFinPos);

            //merge
            SetofOperation merge(speed);
            Operation opMerge(speed, this->current, this->tree, this->isSplit);
            opMerge.type = Operation::MERGE_KEY_TO_PARENT;
            opMerge.SetKey(key);
            merge.AddOperation(opMerge);
            this->SetOperations.push_back(merge);

            //move to finpos
            SetofOperation moveToFinPos2(speed);
            Operation opMoveToFinPos2(speed, this->current, this->tree, this->isSplit);
            opMoveToFinPos2.type = Operation::MOVE_TO_FINPOS;
            opMoveToFinPos2.SetKey(key);
            moveToFinPos2.AddOperation(opMoveToFinPos2);
            this->SetOperations.push_back(moveToFinPos2);

            //move to children node
            SetofOperation moveToChildrenNode(speed);
            Operation opMoveToChildrenNode(speed, this->current, this->tree, this->isSplit);
            opMoveToChildrenNode.type = Operation::MOVE_TO_CHILDREN_NODE;
            opMoveToChildrenNode.SetKey(key);
            moveToChildrenNode.AddOperation(opMoveToChildrenNode);
            this->SetOperations.push_back(moveToChildrenNode);
        
    }

    //highlight
    SetofOperation highlight(speed);
    Operation opHighlight(speed, this->current, this->tree, this->isSplit);
    opHighlight.type = Operation::HIGHLIGHT;
    opHighlight.SetKey(key);
    highlight.AddOperation(opHighlight);
    this->SetOperations.push_back(highlight);

    //normal
    SetofOperation normal(speed);
    Operation opNormal(speed, this->current, this->tree, this->isSplit);
    opNormal.type = Operation::NORMAL;
    opNormal.SetKey(key);
    normal.AddOperation(opNormal);
    this->SetOperations.push_back(normal);

    //insert to leaf
    SetofOperation insertToLeaf(speed);
    Operation opInsertToLeaf(speed, this->current, this->tree, this->isSplit);
    opInsertToLeaf.type = Operation::INSERT_TO_LEAF;
    opInsertToLeaf.SetKey(key);
    insertToLeaf.AddOperation(opInsertToLeaf);
    this->SetOperations.push_back(insertToLeaf);

    //move to finpos
    SetofOperation moveToFinPos(speed);
    Operation opMoveToFinPos(speed, this->current, this->tree, this->isSplit);
    opMoveToFinPos.type = Operation::MOVE_TO_FINPOS;
    opMoveToFinPos.SetKey(key);
    moveToFinPos.AddOperation(opMoveToFinPos);
    this->SetOperations.push_back(moveToFinPos);

    

    return;

}

void TreePresentation::FindKeyOperation(int key){
    if(tree == nullptr) return;
    
    TreeNode * curr = tree;
    int count = 0;
    bool isFound = false;
    while(true){
        if(curr->isLeaf) break;
        count++;
        
        int i = 0;
        for(; i < curr->keys.size(); i++){
            if(curr->keys[i] == key){
                isFound = true;
                break;
            }
            else if(curr->keys[i] > key){
                break;
            }
        }
        if(isFound) break;
        curr = curr->children[i];
    }

    if(isFound){
        for(int i = 0; i < count; i++){
            //highlight
            SetofOperation highlight(speed);
            Operation opHL(speed, this->current, this->tree, this->isSplit);
            opHL.type = Operation::HIGHLIGHT;
            opHL.SetKey(key);
            highlight.AddOperation(opHL);
            this->SetOperations.push_back(highlight);

            //normal
            SetofOperation normal(speed);
            Operation opN(speed, this->current, this->tree, this->isSplit);
            opN.type = Operation::NORMAL;
            opN.SetKey(key);
            normal.AddOperation(opN);
            this->SetOperations.push_back(normal);

            //move to children node
            SetofOperation moveTOchildNode(speed);
            Operation opMoveToChild(speed, this->current, this->tree, this->isSplit);
            opMoveToChild.type = Operation::MOVE_TO_CHILDREN_NODE;
            opMoveToChild.SetKey(key);
            moveTOchildNode.AddOperation(opMoveToChild);
            this->SetOperations.push_back(moveTOchildNode);
            return;
        }
    }
    else{
        int i = 0;
        for(; i < curr->keys.size(); i++){
            if(curr->keys[i] == key){
                isFound = true;
                break;
            }
            else if(curr->keys[i] > key){
                break;
            }
        }
            for(int i = 0; i < count; i++){
                //highlight
                SetofOperation highlight(speed);
                Operation opHL(speed, this->current, this->tree, this->isSplit);
                opHL.type = Operation::HIGHLIGHT;
                opHL.SetKey(key);
                highlight.AddOperation(opHL);
                this->SetOperations.push_back(highlight);

                //normal
                SetofOperation normal(speed);
                Operation opN(speed, this->current, this->tree, this->isSplit);
                opN.type = Operation::NORMAL;
                opN.SetKey(key);
                normal.AddOperation(opN);
                this->SetOperations.push_back(normal);

                //move to children node
                SetofOperation moveTOchildNode(speed);
                Operation opMoveToChild(speed, this->current, this->tree, this->isSplit);
                opMoveToChild.type = Operation::MOVE_TO_CHILDREN_NODE;
                opMoveToChild.SetKey(key);
                moveTOchildNode.AddOperation(opMoveToChild);
                this->SetOperations.push_back(moveTOchildNode);
            }
            //highlight
            SetofOperation highlight(speed);
            Operation opHL(speed, this->current, this->tree, this->isSplit);
            opHL.type = Operation::HIGHLIGHT;
            opHL.SetKey(key);
            highlight.AddOperation(opHL);
            this->SetOperations.push_back(highlight);

            //normal
            SetofOperation normal(speed);
            Operation opN(speed, this->current, this->tree, this->isSplit);
            opN.type = Operation::NORMAL;
            opN.SetKey(key);
            normal.AddOperation(opN);
            this->SetOperations.push_back(normal);
    }
    return;
}

void TreePresentation::DeleteKeyOperation(int key){
    if(tree == nullptr) return;
    TreeNode * curr = tree;
    int count = 0;
    int countMerge = 0;
    //int countSpecial = 0;
    std::cout<<"Cbi tinh toan de delete"<<std::endl;
    bool isFound = false;
    while(true){
        if(curr->isLeaf) break;
        count++;
        int i = 0;
        for(; i < curr->keys.size(); i++){
            if(curr->keys[i] == key){
                std::cout<<"da tim thay key"<<std::endl;
                isFound = true;
            }
            else if(curr->keys[i] > key){
                break;
            }
        }
        if(curr == tree){
            if(curr->keys.size() == 1){
                if(!curr->isLeaf && curr->children[0]->keys.size() == 1 && curr->children[1]->keys.size() == 1){
                    countMerge++;
                }
            }
        }
        curr = curr->children[i];
        
    }
    count;
    if(isFound){
        int newKey = curr->keys[0];
        std::cout<<"newKey: "<<newKey<<std::endl;
        //this->current = this->tree;
        
        for(int i = 0; i < count - countMerge; i++){
            //highlight
            SetofOperation highlight(speed);
            Operation opHL(speed, this->current, this->tree, this->isSplit);
            opHL.type = Operation::HIGHLIGHT;
            opHL.SetKey(key);
            highlight.AddOperation(opHL);
            this->SetOperations.push_back(highlight);

            //normal
            SetofOperation normal(speed);
            Operation opN(speed, this->current, this->tree, this->isSplit);
            opN.type = Operation::NORMAL;
            opN.SetKey(key);
            normal.AddOperation(opN);
            this->SetOperations.push_back(normal);

            

            //merge to child
            SetofOperation mergeToChild(speed);
            Operation opMergeToChild(speed, this->current, this->tree, this->isSplit);
            opMergeToChild.type = Operation::MERGE_TO_CHILDREN;
            opMergeToChild.SetKey(key);
            mergeToChild.AddOperation(opMergeToChild);
            this->SetOperations.push_back(mergeToChild);

            

            //move to finpos
            SetofOperation moveToFinPos(speed);
            Operation opMoveToFinPos(speed, this->current, this->tree, this->isSplit);
            opMoveToFinPos.type = Operation::MOVE_TO_FINPOS;
            opMoveToFinPos.SetKey(key);
            moveToFinPos.AddOperation(opMoveToFinPos);
            this->SetOperations.push_back(moveToFinPos);

            //change key
            SetofOperation changeKey(speed);
            Operation opChangeKey(speed, this->current, this->tree, this->isSplit);
            opChangeKey.type = Operation::CHANGE_KEY;
            opChangeKey.SetKey(key);
            opChangeKey.SetNewKey(newKey);
            changeKey.AddOperation(opChangeKey);
            this->SetOperations.push_back(changeKey);

            //move to children node
            SetofOperation moveToChildrenNode(speed);
            Operation opMoveToChildrenNode(speed, this->current, this->tree, this->isSplit);
            opMoveToChildrenNode.type = Operation::MOVE_TO_CHILDREN_NODE;
            opMoveToChildrenNode.SetKey(newKey);
            moveToChildrenNode.AddOperation(opMoveToChildrenNode);
            this->SetOperations.push_back(moveToChildrenNode);
        }
        //highlight
        SetofOperation highlight(speed);
        Operation opHL(speed, this->current, this->tree, this->isSplit);
        opHL.type = Operation::HIGHLIGHT;
        opHL.SetKey(key);
        highlight.AddOperation(opHL);
        this->SetOperations.push_back(highlight);

        //normal
        SetofOperation normal(speed);
        Operation opN(speed, this->current, this->tree, this->isSplit);
        opN.type = Operation::NORMAL;
        opN.SetKey(key);
        normal.AddOperation(opN);
        this->SetOperations.push_back(normal);

        //remove leaf
        SetofOperation removeLeaf(speed);
        Operation opRemoveLeaf(speed, this->current, this->tree, this->isSplit);
        opRemoveLeaf.type = Operation::REMOVE_LEAF;
        opRemoveLeaf.SetKey(key);
        opRemoveLeaf.SetNewKey(newKey);
        removeLeaf.AddOperation(opRemoveLeaf);
        this->SetOperations.push_back(removeLeaf);
    }
    else{
        std::cout<<"Count merge:"<<countMerge<<std::endl;
        std::cout<<"Count: "<<count<<std::endl;
        for(int i = 0; i < count - countMerge; i++){
            //highlight
            SetofOperation highlight(speed);
            Operation opHL(speed, this->current, this->tree, this->isSplit);
            opHL.type = Operation::HIGHLIGHT;
            opHL.SetKey(key);
            highlight.AddOperation(opHL);
            this->SetOperations.push_back(highlight);

            //normal
            SetofOperation normal(speed);
            Operation opN(speed, this->current, this->tree, this->isSplit);
            opN.type = Operation::NORMAL;
            //merge to child
            SetofOperation mergeToChild(speed);
            Operation opMergeToChild(speed, this->current, this->tree, this->isSplit);
            opMergeToChild.type = Operation::MERGE_TO_CHILDREN;
            opMergeToChild.SetKey(key);
            mergeToChild.AddOperation(opMergeToChild);
            this->SetOperations.push_back(mergeToChild);

            //move to finpos
            SetofOperation moveToFinPos(speed);
            Operation opMoveToFinPos(speed, this->current, this->tree, this->isSplit);
            opMoveToFinPos.type = Operation::MOVE_TO_FINPOS;
            opMoveToFinPos.SetKey(key);
            moveToFinPos.AddOperation(opMoveToFinPos);
            this->SetOperations.push_back(moveToFinPos);

            //move to children node
            SetofOperation moveTOchildNode(speed);
            Operation opMoveToChild(speed, this->current, this->tree, this->isSplit);
            opMoveToChild.type = Operation::MOVE_TO_CHILDREN_NODE;
            opMoveToChild.SetKey(key);
            moveTOchildNode.AddOperation(opMoveToChild);
            this->SetOperations.push_back(moveTOchildNode);
        }
        //highlight
        SetofOperation highlight(speed);
        Operation opHL(speed, this->current, this->tree, this->isSplit);
        opHL.type = Operation::HIGHLIGHT;
        opHL.SetKey(key);
        highlight.AddOperation(opHL);
        this->SetOperations.push_back(highlight);

        //normal
        SetofOperation normal(speed);
        Operation opN(speed, this->current, this->tree, this->isSplit);
        opN.type = Operation::NORMAL;
        opN.SetKey(key);
        normal.AddOperation(opN);
        this->SetOperations.push_back(normal);

        //remvoe leaf
        SetofOperation removeLeaf(speed);
        Operation opRemoveLeaf(speed, this->current, this->tree, this->isSplit);
        opRemoveLeaf.type = Operation::REMOVE_LEAF;
        opRemoveLeaf.SetKey(key);
        removeLeaf.AddOperation(opRemoveLeaf);
        this->SetOperations.push_back(removeLeaf);
    }
}

void TreePresentation::CreateTree(int numofKey){
    // this->tree = this->tree->CreateTree(numofKey);
    // this->tree->calculateCoordinate({800, 100});
    // std::cout<<"da tao tree roi"<<std::endl;

    //move to finpos
    SetofOperation moveToFinPos(speed);
    Operation opMoveToFinPos(speed, this->current, this->tree, this->isSplit);
    opMoveToFinPos.type = Operation::MOVE_TO_FINPOS;
    opMoveToFinPos.SetKey(0); // Không cần key cho thao tác này
    moveToFinPos.AddOperation(opMoveToFinPos);
    this->SetOperations.push_back(moveToFinPos);

}