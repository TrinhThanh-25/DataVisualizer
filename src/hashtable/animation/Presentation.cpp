#include "HashTable/animation/Presentation.h"
#include "HashTable/animation/hashtableCode.h"

Presentation::Presentation(float &speed, HashTable& table, std::vector<std::vector<HashTable>> &historyState, std::vector<std::vector<int>> & historyCode, CodeBlock & codeBlock, int &currentPresentationIndex, int&currentStateIndex)
    : speed(speed), table(table), historyState(historyState), historyCode(historyCode), codeBlock(codeBlock), currentStep(0), currentPresentationIndex(currentPresentationIndex), currentStateIndex(currentStateIndex){}

void Presentation::InsertNodeAnimation(int key, Node* newNode) {
    
    int bucket = key % table.GetSize();
    codeBlock.setCode(hashinsertCode);
    
    // Duyệt qua các node trong bucket để tạo animation tuần tự
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;

    // Bước 1: Highlight lần lượt từng node trong bucket
    while (current != newNode && current != nullptr) {
        SetofAnimation set(speed);
        Animation highlight(speed, current, codeBlock);
        highlight.type = 1;
        set.AddAnimation(highlight);
        SetAnimations.push_back(set); // Thêm set để thực thi tuần tự
        

        SetofAnimation settemp(speed);
        Animation normal(speed, current, codeBlock);
        normal.type = 5;
        settemp.AddAnimation(normal);
        SetAnimations.push_back(settemp);

        prev = current;
        current = current->next;
    }

    // Bước 2: Fade in node mới (node 40)
    // Không cần đặt current->isVisual = true ở đây
    SetofAnimation fadeInSet(speed);
    Animation fadeIn(speed, newNode, codeBlock);
    fadeIn.type = 2; // Fade in
    fadeInSet.AddAnimation(fadeIn);
    SetAnimations.push_back(fadeInSet);

    // Bước 3: Vẽ mũi tên từ node trước đó (node 30) đến node mới (node 40)
    if (prev) {
        SetofAnimation edgeSet(speed);
        Animation edge(speed, prev, codeBlock);
        edge.type = 6; // Vẽ mũi tên
        edgeSet.AddAnimation(edge);
        SetAnimations.push_back(edgeSet);
    }
}

void Presentation::DeleteNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;
    Node* nodeToDelete = nullptr;
    codeBlock.setCode(hashremoveCode);

    while (current != nullptr) {
        SetofAnimation highlightNode(speed);
        Animation highlight(speed, current, codeBlock);
        highlight.type = 1;
        highlightNode.AddAnimation(highlight);
        SetAnimations.push_back(highlightNode);

        SetofAnimation normalNode(speed);
        Animation normal(speed, current, codeBlock);
        normal.type = 5;
        normalNode.AddAnimation(normal);
        SetAnimations.push_back(normalNode);


        if (current->data == key) {
            nodeToDelete = current;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (nodeToDelete == nullptr){
        Animation set(speed, current, codeBlock);
        set.type = 8;
        set.code = 4;
        SetofAnimation codeset(speed);
        codeset.AddAnimation(set);
        SetAnimations.push_back(codeset);
        return;
    }

    if (prev && nodeToDelete->next) {
        SetofAnimation edgeSet(speed);
        Animation edge(speed, prev, codeBlock);
        edge.type = 7;
        edgeSet.AddAnimation(edge);
        SetAnimations.push_back(edgeSet);
    }

    SetofAnimation fadeOutSet(speed);
    Animation fadeOut(speed, nodeToDelete, codeBlock);
    fadeOut.type = 3;
    fadeOutSet.AddAnimation(fadeOut);
    SetAnimations.push_back(fadeOutSet);

    Node* nodeAfterDeleted = nodeToDelete->next;
    if (nodeAfterDeleted) {
        SetofAnimation moveSet(speed);
        while (nodeAfterDeleted != nullptr) {
            Vector2 newPosition = {nodeAfterDeleted->position.x, nodeAfterDeleted->position.y - 50};
            nodeAfterDeleted->finalPosition = newPosition;
            
            Animation moveNode(speed, nodeAfterDeleted, newPosition, codeBlock); // Truyền target
            moveNode.type = 4;
            moveSet.AddAnimation(moveNode);
            nodeAfterDeleted = nodeAfterDeleted->next;
        }
        SetAnimations.push_back(moveSet);
    }
}

void Presentation::FindNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);
    codeBlock.setCode(hashfindCode);

    while (current != nullptr) {
        SetofAnimation set(speed);
        Animation highlight(speed, current, codeBlock);
        highlight.type = 1;
        set.AddAnimation(highlight);
        SetAnimations.push_back(set);

        SetofAnimation normalNode(speed);
        Animation normal(speed, current, codeBlock);
        normal.type = 5;
        normalNode.AddAnimation(normal);
        SetAnimations.push_back(normalNode);

        if (current->data == key) break;
        current = current->next;
    }
    if(current){
        Animation set(speed, current, codeBlock);
        set.type = 8;
        set.code = 3;
        SetofAnimation codeset(speed);
        codeset.AddAnimation(set);
        SetAnimations.push_back(codeset);
    }
    else{
        Animation set(speed, current, codeBlock);
        set.type = 8;
        set.code = 4;
        SetofAnimation codeset(speed);
        codeset.AddAnimation(set);
        SetAnimations.push_back(codeset);
    }
}

void Presentation::CreateTableAnimation(int size) {
    if(size < 0) return;
    SetofAnimation fadeInNode(speed);
    SetofAnimation drawEdge(speed);
    for (int i = 0; i < size; i++) {
        Node* current = table.getTable(i);
        while (current != nullptr) {
            Animation fadein(speed, current, codeBlock);
            Animation drawedge(speed, current, codeBlock);

            fadein.type = 2;
            drawedge.type = 6;

            fadeInNode.AddAnimation(fadein);
            drawEdge.AddAnimation(drawedge);

            current = current->next;
        }
    }
    SetAnimations.push_back(fadeInNode);
    SetAnimations.push_back(drawEdge);
}

// void Presentation::UpdateAnimation(int initValue, int finalValue, Node*newNode){
//     if(!table.Find(initValue)){
//         return;
//     }
//     DeleteNodeAnimation(initValue);
//     InsertNodeAnimation(finalValue, newNode);
//     return;
// }

bool Presentation::DrawPresentation() {
    if (SetAnimations.empty() || currentStep >= SetAnimations.size()) return true;

    if (SetAnimations[currentStep].Draw()) {
        
        HashTable tempHash(table);
        if(currentStep == 0){
            currentPresentationIndex++;
            std::vector<HashTable> temp = {};
            temp.push_back(tempHash);
            historyState.push_back(temp);

            std::vector<int> tempVec = {};
            tempVec.push_back(codeBlock.getBackHighlightID());
            historyCode.push_back(tempVec);

            currentStateIndex = historyState.back().size() - 1;
            
            
        }
        else{
            std::cout<<"Dang chay"<<std::endl;
            historyState.back().push_back(tempHash);
            historyCode.back().push_back(codeBlock.getBackHighlightID());
            currentStateIndex = historyState.back().size() - 1;
        }

        currentStep++;
    }
    return currentStep >= SetAnimations.size();
}



void Presentation::clear() {
    SetAnimations.clear();
    //historyOfSets.clear();
    currentStep = 0;
}

