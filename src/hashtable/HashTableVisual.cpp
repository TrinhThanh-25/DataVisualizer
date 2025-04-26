#include "HashTable/HashTableVisual.h"
#include <algorithm>
#include <iostream>

HashTableVisualization::HashTableVisualization(const bool& isLightMode, float &speed)
                                    :  
                                    isLightMode(isLightMode), speed(speed), 
                                    historyState({}), historyCode({}), hashcodeBlock(), currentPresentationIndex(-1), currentStateIndex(0),
                                    presentations(speed, hashTable, historyState, historyCode, hashcodeBlock, currentPresentationIndex, currentStateIndex),
                                    inputPanel(), 
                                    speedSlider(0.1, 5.0f, 1.0f, 100), playbackControl({900, 600}, 200, 10,speed) {

    //inputBox.isAppear = false;
    isRewindingStep = false;
    inputPanel.setDataName("Hash Table");
    hashTable = new HashTable(MAX_TABLE_SIZE);
    //this->historyState = {};
    // currentPresentationIndex = 0;
    // currentStateIndex = 0;

    // insertButton.setPosition({50, 700});
    // insertButton.setSize({150, 50});
    // insertButton.setText("Insert", 20);

    // deleteButton.setPosition({220, 700});
    // deleteButton.setSize({150, 50});
    // deleteButton.setText("Delete", 20);

    // findButton.setPosition({390, 700});
    // findButton.setSize({150, 50});
    // findButton.setText("Find", 20);

    // initButton.setPosition({560, 700});
    // initButton.setSize({150, 50});
    // initButton.setText("Init", 20);

    // rewindStepButton.setPosition({730, 700});
    // rewindStepButton.setSize({150, 50});
    // rewindStepButton.setText("Rewind Step", 20);
}

// HashTableVisualization::~HashTableVisualization() {
//     for (int i = 0; i < hashTable->GetSize(); i++) {
//         Node* current = hashTable->getTable(i);
//         while (current != nullptr) {
//             Node* temp = current;
//             current = current->next;
//             delete temp;
//         }
//     }

//     hashTable->table.clear();
// }

void HashTableVisualization::Init(int size, int numofKey) {
    // Xóa dữ liệu hiện tại của hashTable
    hashTable->InitTable(size, numofKey);
    // Xóa các animation hiện tại trong presentations
    presentations.clear();

    // Gọi CreateTableAnimation để tạo animation cho bảng mới
    presentations.CreateTableAnimation(size);

    // isInitializing = false;
    // inputBox.isAppear = false;
}

void HashTableVisualization::Insert(int key) {
    if(key == -1) return;
    hashTable->Insert(key);
    std::cout<<"Co co"<<std::endl;
    Node* newNode = hashTable->getTable(key % hashTable->GetSize());
    while (newNode && newNode->data != key) newNode = newNode->next;
    //presentations.clear();
    presentations.InsertNodeAnimation(key, newNode);
    // isInserting = false;
    // inputBox.isAppear = false;
}

void HashTableVisualization::Delete(int key) {
    if(key == -1) return;
    presentations.clear();
    presentations.DeleteNodeAnimation(key);
    this->key = key; // Lưu key để dùng trong DrawHashTable
    deleting = true; // Đánh dấu để xóa sau khi animation hoàn tất
    //isDeleting = false;
    // inputBox.isAppear = false;
}

bool HashTableVisualization::Find(int key) {
    if(key == -1) return false;
    presentations.FindNodeAnimation(key);
    //isFinding = false;
    //inputBox.isAppear = false;
    return hashTable->Find(key);
}

void HashTableVisualization::UpdateKey(int initValue, int finalValue){
    if(initValue == -1 || finalValue == -1) return;
    if(!hashTable->Find(initValue)){
        return;
    }

    Delete(initValue);
    Insert(finalValue);
    return;
}

// void HashTableVisualization::HandleInput() {
//     if(IsKeyPressed(KEY_T)){
//         isRewindingStep = true;
//     }
//     else if(IsKeyPressed(KEY_R)){
//         isRewindingStep = false;
//         currentPresentationIndex = historyState.size() - 1;
//         currentStateIndex = historyState[currentPresentationIndex].size() - 1;
//     }
//     if(isRewindingStep){
//         playbackControl.UpdateHash(currentPresentationIndex, currentStateIndex, historyState);
//     }
//     // if (IsKeyPressed(KEY_LEFT) && isRewindingStep && !historyState.empty()) {
//     //     if (currentStateIndex == 0) {
//     //         if (currentPresentationIndex > 0) {
//     //             currentPresentationIndex--;
//     //             currentStateIndex = historyState[currentPresentationIndex].size() - 1;
//     //         }
//     //     } else {
//     //         currentStateIndex--;
//     //     }
//     // }
// }

void HashTableVisualization::Update(){
    inputPanel.setBackActive();
    inputPanel.update();
    //playbackControl.UpdateHash(currentPresentationIndex, currentStateIndex, historyState);
    

    if(inputPanel.IsRandomPressed()){
        this->isPlaying = true;
        this->isCreate = true;
        std::random_device rd; // Tạo seed
        std::mt19937 gen(rd()); // Engine ngẫu nhiên
        std::uniform_int_distribution<> dis(10, 20); // Khoảng [1, 100]

        int randomNum = dis(gen); // Random một số
        presentations.clear();

        Init(randomNum, 2 * randomNum);
    }
    
     // Kiểm tra nếu người dùng chọn file để nhập dữ liệu
     int activeButton;
     bool isfile = false;
     std::vector<int> inputValue;
     std::vector<std::vector<int>> fileValues;
     if (inputPanel.IsLoadFilePressed()) {
        isfile = true;
        fileValues = inputPanel.GetFileValues2D();
        activeButton = inputPanel.GetActiveButtonIndex();
        std::cout<<fileValues[0][0]<<std::endl;
        //this->isPlaying = true;

        if (!fileValues.empty()) {
            this->isPlaying = true;
            switch (activeButton) {
                case 0: { // Create/Init
                    if (fileValues.size() >= 2 && !fileValues[0].empty()) {
                        int size = fileValues[0][0]; // Dòng 1: số bucket
                        std::vector<int> keys = fileValues[1]; // Dòng 2: các key
                        hashTable->CreateTableFile(keys);
                        this->isCreate = true;
                        presentations.clear();
                        presentations.CreateTableAnimation(hashTable->GetSize());
                    } else {
                        std::cout << "File không đúng định dạng cho Init: cần ít nhất 2 dòng, dòng 1 là số bucket, dòng 2 là các key\n";
                    }
                    break;
                }
                case 1: { // Search
                    if (!fileValues[0].empty()) {
                        int key = fileValues[0][0];
                        this->isCreate = false;
                        presentations.clear();
                        Find(key);
                    }
                    break;
                }
                case 2: { // Insert
                    if (!fileValues[0].empty()) {
                        int key = fileValues[0][0];
                        this->isCreate = false;
                        std::cout<<"Co insert file"<<key<<std::endl;
                        presentations.clear();
                        Insert(key);
                    }
                    break;
                }
                case 3: { // Delete
                    if (!fileValues[0].empty()) {
                        int key = fileValues[0][0];
                        this->isCreate = false;
                        presentations.clear();
                        Delete(key);
                    }
                    break;
                }
            }
            inputPanel.ResetInputState();
        }
    } else {
        isfile = false;
        // Xử lý dữ liệu từ ô nhập liệu (nếu không dùng file)
        inputValue = inputPanel.GetInputText();
        activeButton = inputPanel.GetActiveButtonIndex();

        if (inputValue.empty() == false && activeButton != -1 ) {
            lastactiveButton = activeButton;
            lastinputValue = inputValue;
            //this->isPlaying = true;
            switch (activeButton) {
                case 0: {
                    presentations.clear();
                    Init(inputValue[0], 2 * inputValue[0]);
                    this->isPlaying = true;
                    this->isCreate = true;
                    break;
                }
                case 1: this->isCreate = false; presentations.clear(); Find(inputValue[0]); this->isPlaying = true; break;
                case 2: this->isCreate = false; presentations.clear(); Insert(inputValue[0]); this->isPlaying = true; break;
                case 3: this->isCreate = false; presentations.clear(); Delete(inputValue[0]); this->isPlaying = true; break;
                case 4:{
                    if(inputValue.size() == 2){
                        this->isCreate = false;
                        presentations.clear();
                        UpdateKey(inputValue[0], inputValue[1]);
                    }
                    break;
                }
            }
            inputPanel.ResetInputState();
        }
    }

    // if(IsKeyPressed(KEY_R)){
    //     historyState.pop_back();
    //     historyCode.pop_back();
    //     currentPresentationIndex = historyState.size() - 1;
    //     currentStateIndex = historyState.back().size() - 1;
    //     if(isfile == false){
    //         switch (activeButton)
    //         {
    //         case 1: Find(lastinputValue[0]); break;
    //         case 2: {hashTable->Delete(lastinputValue[0]); Insert(lastinputValue[0]); this->isPlaying = true; break;}
    //         case 3: {hashTable->Insert(lastinputValue[0], ""); Delete(lastinputValue[0]); this->isPlaying = true; break;}
    //         case 4:{
    //             if(inputValue.size() == 2){
    //                 hashTable->Insert(lastinputValue[0], "");
    //                 hashTable->Delete(lastinputValue[1]);
    //                 this->isPlaying = true;
    //                 UpdateKey(lastinputValue[0], lastinputValue[1]);
    //             }
    //             break;
    //         }
    //         }
    //     }
    // }
    // if(IsKeyPressed(KEY_SPACE)){
    //     this->isPlaying = !this->isPlaying;
    // }

    if(inputPanel.isPlayPressed()){
        if(historyState.size() >= 2 && this->isPlaying == false && presentations.currentStep >= presentations.SetAnimations.size() && !this->isCreate){
            historyState.pop_back();
            historyCode.pop_back();
            currentPresentationIndex = historyState.size() - 1;
            
            currentStateIndex = historyState.back().size() - 1;
            hashTable = new HashTable(historyState.back().back());
            // std::cout<<historyState.size()<<std::endl;
            if(isfile == false){
                switch (activeButton)
                {
                case 1: Find(lastinputValue[0]); break;
                case 2: {presentations.clear(); Insert(lastinputValue[0]); this->isPlaying = true; break;}
                case 3: {presentations.clear(); Delete(lastinputValue[0]); this->isPlaying = true; break;}
                case 4:{
                    if(lastinputValue.size() == 2){
                        this->isPlaying = true;
                        UpdateKey(lastinputValue[0], lastinputValue[1]);
                    }
                    break;
                }
                }
            }
        }
        else if(this->isPlaying){
            this->isPlaying = false;
        }
        else if(!this->isPlaying){
            this->isPlaying = true;
        }
    }
    

    if(this->isPlaying){
        if (presentations.DrawPresentation()) {
            speed = speedSlider.val * 0.02f;
            this->isPlaying = false;
            this->isDrawTable = true;
            this->isSkipBack = false;
            inputPanel.setEnd();
            if (deleting) {
                hashTable->Delete(key);
                deleting = false;
            }
        }
        else{
            inputPanel.deEnd();
            this->isPlaying = true;
        }
    }

    if(this->isCreate){
        inputPanel.deEnd();
        inputPanel.setPause();
    }
    if(this->isPlaying){
        inputPanel.dePause();
    }
    else if(!this->isPlaying){
        inputPanel.setPause();
    }

    speedSlider.Update();
    
    if(isPlaying == true){
        isRewindingStep = false;
        if(inputPanel.isEndPressed()){
            this->isSkipBack = true;
        }
        if(this->isSkipBack){
            isDrawTable = false;
            speed = 1.0f;
        }
        else{
            speed = speedSlider.val * 0.02f;
        }
    }
    else{
        speed = speedSlider.val * 0.02f;
        if(inputPanel.isNextPressed()){
            this->isRewindingStep = true;
            currentStateIndex++;
            if(currentStateIndex == historyState[currentPresentationIndex].size()){
                currentPresentationIndex++;
                currentStateIndex = 0;
                if(currentPresentationIndex == historyState.size()){
                    this->isRewindingStep = false;
                    currentPresentationIndex = historyState.size() - 1;
                    currentStateIndex = historyState.back().size() - 1;
                }
            }
        }
        else if(inputPanel.isEndPressed()){
            this->isRewindingStep = false;
            currentPresentationIndex = historyState.size() - 1;
            currentStateIndex = historyState.back().size() - 1;
        }
        else if(inputPanel.isPrevPressed()){
            this->isRewindingStep = true;
            currentStateIndex--;
            if(currentStateIndex < 0){
                currentPresentationIndex--;
                if(currentPresentationIndex < 0){
                    currentPresentationIndex = 0;
                    currentStateIndex = 0;
                }
                else{
                    currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                }
            }
        }
        else if(inputPanel.isStartPressed()){
            this->isRewindingStep = true;
            currentPresentationIndex--;
            if(currentPresentationIndex < 0){
                currentPresentationIndex = 0;
            }
            currentStateIndex = historyState[currentPresentationIndex].size() - 1;
        }
        
    }

}


void HashTableVisualization::DrawHashTable() {
    int bucketSpacing = 50;
    int startX = 200;
    int startY = 150;

    

    if(!isRewindingStep){
        if(isDrawTable){
            if(!hashTable->isEmpty){
                for (int i = 0; i < hashTable->GetSize(); i++) {
                    Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
                    DrawCircle(bucketPos.x, bucketPos.y, 10, nodeHighlightColor);
                    DrawText(std::to_string(i).c_str(), bucketPos.x - 5, bucketPos.y + 15, 15, nodeTextColor);
            
                    Node* current = hashTable->getTable(i);
                    Vector2 prevPos = bucketPos;
                    while (current != nullptr) {
                        if (current->isVisual) {
                            
                            if (current->next) {
                                DrawLink(current->position, {current->arrowPos.x, current->arrowPos.y - current->size.x});
                            }
                            DrawNode(current);
                        }
                        prevPos = current->position;
                        current = current->next;
                    }
                }
            }
        }
    }
    else{
        //std::cout<<currentPresentationIndex<<" "<<currentStateIndex;
        // if(currentPresentationIndex == 0) return;
        codeBlock.setHighlight({historyCode[currentPresentationIndex][currentStateIndex]});
        for(int i = 0; i < historyState[currentPresentationIndex][currentStateIndex]->size; i++){

            Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
            DrawCircle(bucketPos.x, bucketPos.y, 10, nodeHighlightColor);
            DrawText(std::to_string(i).c_str(), bucketPos.x - 5, bucketPos.y + 15, 15, nodeTextColor);
    
            Node* current = historyState[currentPresentationIndex][currentStateIndex]->getTable(i);
            Vector2 prevPos = bucketPos;
            while (current != nullptr) {
                if (current->isVisual) {
                    
                    if (current->next) {
                        DrawLink(current->position, {current->arrowPos.x, current->arrowPos.y - current->size.x});
                    }
                    DrawNode(current);
                }
                prevPos = current->position;
                current = current->next;
            }
        }
    }
    hashcodeBlock.draw();
}

void HashTableVisualization::DrawNode(Node* node) {
    if(node->isChosen){
        node->colorCurrent = nodeHighlightColor;
        node->textCurColor = nodeHighlightTextColor;
    }
    else{
        node->colorCurrent = nodeColor;
        node->textCurColor = nodeTextColor;
    }
    DrawCircle(node->position.x, node->position.y, node->size.x, node->colorCurrent);
    DrawCircleLines(node->position.x, node->position.y, node->size.x, WHITE);
    std::string text = std::to_string(node->data);
    int textWidth = MeasureText(text.c_str(), 15);
    DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - 7, 15, node->textCurColor);
}

void HashTableVisualization::DrawLine(Vector2 start, Vector2 end) {
    DrawLineEx(start, end, 3, appTitleColor);
}

void HashTableVisualization::DrawArrow(Vector2 start, Vector2 end) {
    Vector2 diff = Vector2Subtract(end, start);
    float length = Vector2Length(diff);
    if (length < 0.001f) return;

    Vector2 dir = Vector2Normalize(diff);
    float arrowSize = 10.0f;
    Vector2 left = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 150.0f), arrowSize));
    Vector2 right = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 210.0f), arrowSize));
    DrawLineEx(end, left, 2, BLACK);
    DrawLineEx(end, right, 2, BLACK);
}

void HashTableVisualization::DrawLink(Vector2 start, Vector2 end) {
    // Vẽ đường thẳng từ start đến end
    DrawLineEx(start, end, 2, appTitleColor);

    // Tính toán hướng và kích thước của mũi tên
    Vector2 diff = Vector2Subtract(end, start);
    float length = Vector2Length(diff);
    if (length < 0.001f) return; // Tránh trường hợp đường thẳng quá ngắn

    Vector2 dir = Vector2Normalize(diff);
    float arrowSize = 10.0f; // Kích thước của đầu mũi tên (có thể điều chỉnh)

    // Tính toán các điểm của tam giác đầu mũi tên
    Vector2 tip = end; // Đỉnh của tam giác (điểm kết thúc)
    Vector2 baseLeft = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 150.0f), arrowSize));
    Vector2 baseRight = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 210.0f), arrowSize));

    // Vẽ tam giác đầy (filled triangle) làm đầu mũi tên
    DrawTriangle(tip, baseLeft, baseRight, appTitleColor);
}


void HashTableVisualization::Draw() {
    DrawHashTable();

    inputPanel.draw();
    
    speedSlider.Draw();
    //playbackControl.Draw();
}

bool HashTableVisualization::isBackPressed() {
    bool res = inputPanel.isBackPressed();
    if (res) {
        inputPanel.reset();
        speedSlider.reset();
        presentations.clear();
        isRewindingStep = false;
        currentPresentationIndex = -1;
        currentStateIndex = 0;
        historyState.clear();
        historyCode.clear();
        hashTable = new HashTable(MAX_TABLE_SIZE);
        hashcodeBlock.clearCode();
        hashcodeBlock.clearHighlight();
        //this->isPlaying = true;
    }
    return res;
}