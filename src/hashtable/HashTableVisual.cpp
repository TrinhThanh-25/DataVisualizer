#include "HashTable/HashTableVisual.h"
#include <algorithm>
#include <iostream>

HashTableVisualization::HashTableVisualization(const bool& isLightMode, float &speed)
                                    : hashTable(MAX_TABLE_SIZE), 
                                    isLightMode(isLightMode), speed(speed), 
                                    historyState({}),currentPresentationIndex(-1), currentStateIndex(0),
                                    presentations(speed, hashTable, historyState, currentPresentationIndex, currentStateIndex),
                                    inputPanel({30, 700}, {150, 200}, LIGHTGRAY), 
                                    speedSlider(0.01f, 0.1f, 0.05f, 10), playbackControl({900, 600}, 200, 10) {

    //inputBox.isAppear = false;
    isRewindingStep = false;
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
//     for (int i = 0; i < hashTable.GetSize(); i++) {
//         Node* current = hashTable.getTable(i);
//         while (current != nullptr) {
//             Node* temp = current;
//             current = current->next;
//             delete temp;
//         }
//     }

//     hashTable.table.clear();
// }

void HashTableVisualization::Init(int size, int numofKey) {
    // Xóa dữ liệu hiện tại của hashTable
    hashTable.InitTable(size, numofKey);
    // Xóa các animation hiện tại trong presentations
    presentations.clear();

    // Gọi CreateTableAnimation để tạo animation cho bảng mới
    presentations.CreateTableAnimation(size);

    // isInitializing = false;
    // inputBox.isAppear = false;
}

void HashTableVisualization::Insert(int key) {
    hashTable.Insert(key, "");
    Node* newNode = hashTable.getTable(key % hashTable.GetSize());
    while (newNode && newNode->data != key) newNode = newNode->next;
    presentations.InsertNodeAnimation(key, newNode);
    // isInserting = false;
    // inputBox.isAppear = false;
}

void HashTableVisualization::Delete(int key) {
    presentations.DeleteNodeAnimation(key);
    this->key = key; // Lưu key để dùng trong DrawHashTable
    deleting = true; // Đánh dấu để xóa sau khi animation hoàn tất
    //isDeleting = false;
    // inputBox.isAppear = false;
}

bool HashTableVisualization::Find(int key) {
    presentations.FindNodeAnimation(key);
    //isFinding = false;
    //inputBox.isAppear = false;
    return hashTable.Find(key);
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
    inputPanel.Update();
    playbackControl.UpdateHash(currentPresentationIndex, currentStateIndex, historyState);
    if(playbackControl.isPlaying){
        isRewindingStep = true;
    }
    else{
        isRewindingStep = false;
    }

    int inputValue = inputPanel.GetInputText();
    int activeButton = inputPanel.GetActiveButtonIndex();

    if(inputValue != -1 && activeButton != -1){
        switch (activeButton)
        {
        case 0: Init(inputValue, 2 * inputValue); break;
        case 1: Find(inputValue); break;
        case 2: Insert(inputValue); break;
        case 3: Delete(inputValue); break;
        }
        inputPanel.ResetInputState();
            
    }
    speedSlider.Update();
    speed = speedSlider.val;

}


void HashTableVisualization::DrawHashTable() {
    int bucketSpacing = 50;
    int startX = 200;
    int startY = 150;

    if (presentations.DrawPresentation()) {
        if (deleting) {
            hashTable.Delete(key);
            deleting = false;
        }
    }

    if(!isRewindingStep){
        for (int i = 0; i < hashTable.GetSize(); i++) {
            Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
            DrawCircle(bucketPos.x, bucketPos.y, 10, nodeHighlightColor);
            DrawText(std::to_string(i).c_str(), bucketPos.x - 5, bucketPos.y + 15, 15, nodeTextColor);
    
            Node* current = hashTable.getTable(i);
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
    else{
        //std::cout<<currentPresentationIndex<<" "<<currentStateIndex;
        // if(currentPresentationIndex == 0) return;
        for(int i = 0; i < historyState[currentPresentationIndex][currentStateIndex].size; i++){

            Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
            DrawCircle(bucketPos.x, bucketPos.y, 10, nodeHighlightColor);
            DrawText(std::to_string(i).c_str(), bucketPos.x - 5, bucketPos.y + 15, 15, nodeTextColor);
    
            Node* current = historyState[currentPresentationIndex][currentStateIndex].getTable(i);
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

void HashTableVisualization::DrawNode(Node* node) {
    DrawCircle(node->position.x, node->position.y, node->size.x, node->colorCurrent);
    DrawCircleLines(node->position.x, node->position.y, node->size.x, WHITE);
    std::string text = std::to_string(node->data);
    int textWidth = MeasureText(text.c_str(), 15);
    DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - 7, 15, node->textCurColor);
}

void HashTableVisualization::DrawLine(Vector2 start, Vector2 end) {
    DrawLineEx(start, end, 2, BLACK);
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
    DrawLineEx(start, end, 2, BLACK);

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
    DrawTriangle(tip, baseLeft, baseRight, BLACK);
}


void HashTableVisualization::Draw() {
    DrawHashTable();

    inputPanel.Draw();
    
    speedSlider.Draw();
    playbackControl.Draw();
}