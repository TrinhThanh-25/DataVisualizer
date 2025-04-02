#include "HashTable/HashTableVisual.h"
#include <algorithm>

HashTableVisualization::HashTableVisualization(const Texture2D& hollowCircle, const Texture2D& solidCircle, const Texture2D& arrowEdge, const Font& fontNumber, const Font& fontText, const bool& isLightMode, const float& speed)
    : hashTable(MAX_TABLE_SIZE), hollowCircle(hollowCircle), solidCircle(solidCircle), arrowEdge(arrowEdge), fontNumber(fontNumber), fontText(fontText), isLightMode(isLightMode), speed(speed), presentations(fontNumber, fontText, speed, hashTable),
      isInserting(false), isDeleting(false), isFinding(false), isInitializing(false), inputBox(10, HASH_TABLE_HEIGHT - 50, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT) {
    
    inputBox.isAppear = false;

    insertButton.setPosition({50, 700});
    insertButton.setSize({150, 50});
    insertButton.setText("Insert", 20);
    insertButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    deleteButton.setPosition({220, 700});
    deleteButton.setSize({150, 50});
    deleteButton.setText("Delete", 20);
    deleteButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    findButton.setPosition({390, 700});
    findButton.setSize({150, 50});
    findButton.setText("Find", 20);
    findButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    initButton.setPosition({560, 700});
    initButton.setSize({150, 50});
    initButton.setText("Init", 20);
    initButton.setColor({80, 80, 80, 255}, GRAY, BLACK);
}

HashTableVisualization::~HashTableVisualization() {
    for (int i = 0; i < hashTable.GetSize(); i++) {
        Node* current = hashTable.getTable(i);
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void HashTableVisualization::Init(int size) {
    // Xóa dữ liệu hiện tại của hashTable
    for (int i = 0; i < hashTable.GetSize(); i++) {
        Node* current = hashTable.getTable(i);
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Tạo lại hashTable với kích thước mới
    hashTable = HashTable(size);

    // Xóa các animation hiện tại trong presentations
    presentations.clear();

    // Gọi CreateTableAnimation để tạo animation cho bảng mới
    presentations.CreateTableAnimation(size);

    isInitializing = false;
    inputBox.isAppear = false;
}

void HashTableVisualization::Insert(int key) {
    hashTable.Insert(key, "");
    Node* newNode = hashTable.getTable(key % hashTable.GetSize());
    while (newNode && newNode->data != key) newNode = newNode->next;
    presentations.InsertNodeAnimation(key, newNode);
    isInserting = false;
    inputBox.isAppear = false;
}

void HashTableVisualization::Delete(int key) {
    presentations.DeleteNodeAnimation(key);
    hashTable.Delete(key);
    isDeleting = false;
    inputBox.isAppear = false;
}

bool HashTableVisualization::Find(int key) {
    presentations.FindNodeAnimation(key);
    isFinding = false;
    inputBox.isAppear = false;
    return hashTable.Find(key);
}

void HashTableVisualization::HandleInput() {
    if (inputBox.isAppear) inputBox.Update();
    if (IsKeyPressed(KEY_ENTER) && inputBox.isAppear) {
        std::string text = inputBox.GetText();
        inputBox.clearText();
        if (!text.empty() && std::all_of(text.begin(), text.end(), ::isdigit)) {
            int key = std::stoi(text);
            if (isInserting) Insert(key);
            else if (isDeleting) Delete(key);
            else if (isFinding) Find(key);
            else if (isInitializing) Init(key);
        }
        inputBox.isAppear = false;
    }
}

void HashTableVisualization::HandleMouseInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (insertButton.isPressed()) {
            isInserting = true;
            inputBox.isAppear = true;
        } else if (deleteButton.isPressed()) {
            isDeleting = true;
            inputBox.isAppear = true;
        } else if (findButton.isPressed()) {
            isFinding = true;
            inputBox.isAppear = true;
        } else if (initButton.isPressed()) {
            isInitializing = true;
            inputBox.isAppear = true;
        }
    }
}

void HashTableVisualization::DrawHashTable() {
    int bucketSpacing = 50;
    int startX = 20;
    int startY = 50;

    for (int i = 0; i < hashTable.GetSize(); i++) {
        Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
        DrawCircle(bucketPos.x, bucketPos.y, 10, BLACK);
        DrawText(std::to_string(i).c_str(), bucketPos.x - 5, bucketPos.y + 15, 15, RED);

        Node* current = hashTable.getTable(i);
        Vector2 prevPos = bucketPos;
        while (current != nullptr) {
            DrawNode(current);
            if (current != hashTable.getTable(i)) {
                DrawLink(prevPos, {current->position.x, current->position.y - 10});
            }
            prevPos = current->position;
            current = current->next;
        }
    }
}

void HashTableVisualization::DrawNode(Node* node) {
    DrawCircle(node->position.x, node->position.y, node->size.x, node->colorCurrent);
    DrawCircleLines(node->position.x, node->position.y, node->size.x, WHITE);
    std::string text = std::to_string(node->data);
    int textWidth = MeasureText(text.c_str(), 15);
    DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - 7, 15, WHITE);
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

    // Vẽ mũi tên ở điểm end
    Vector2 diff = Vector2Subtract(end, start);
    float length = Vector2Length(diff);
    if (length < 0.001f) return; // Tránh trường hợp đường thẳng quá ngắn

    Vector2 dir = Vector2Normalize(diff);
    float arrowSize = 10.0f;
    Vector2 left = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 150.0f), arrowSize));
    Vector2 right = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 210.0f), arrowSize));
    DrawLineEx(end, left, 2, BLACK);
    DrawLineEx(end, right, 2, BLACK);
}


void HashTableVisualization::Draw() {
    DrawHashTable();
    presentations.DrawPresentation();

    insertButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    deleteButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    findButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    initButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});

    if (inputBox.isAppear) inputBox.Draw();
}