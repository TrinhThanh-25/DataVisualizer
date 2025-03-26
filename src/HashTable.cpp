#include "HashTable.h"
#include <ctime> // Để sử dụng time() trong InitTable

HashTable::HashTable(int size) {
    this->size = size;
    table.resize(size);
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

Node* HashTable::getTable(int index) {
    return table[index];
}

int HashTable::GetSize() const {
    return size;
}

void HashTable::Insert(int key, const std::string& value) {
    int index = key % size;
    Node* newNode = new Node(key, {static_cast<float>(index * 50 + 20), 50.0f}, {15, 15}, BLACK, RED);
    
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        Node* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->position = {current->position.x, current->position.y + 50};
        newNode->finalPosition = newNode->position;
    }
}

void HashTable::Delete(int key) {
    int index = key % size;
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr && current->data != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Không tìm thấy key

    if (prev == nullptr) {
        table[index] = current->next;
        if (table[index] != nullptr) {
            table[index]->position = {static_cast<float>(index * 50 + 20), 50.0f};
            table[index]->finalPosition = table[index]->position;
        }
        delete current;
    } else {
        prev->next = current->next;
        delete current;
    }

    // Cập nhật vị trí các node còn lại
    current = table[index];
    float yPos = 50.0f;
    while (current != nullptr) {
        current->position = {static_cast<float>(index * 50 + 20), yPos};
        current->finalPosition = current->position;
        yPos += 50.0f;
        current = current->next;
    }
}

bool HashTable::Find(int key) const {
    int index = key % size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->data == key) return true;
        current = current->next;
    }
    return false;
}

void HashTable::InitTable(int size) {
    // Xóa dữ liệu hiện tại của HashTable
    for (int i = 0; i < this->size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }

    // Cập nhật kích thước mới
    this->size = size;
    table.resize(size);
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }

    // Khởi tạo seed cho số ngẫu nhiên
    srand(static_cast<unsigned int>(time(0)));

    // Tạo dữ liệu ngẫu nhiên
    for (int i = 0; i < size; ++i) {
        int randomSizeList = rand() % 8; // Số lượng node ngẫu nhiên trong mỗi bucket (0-7)
        for (int j = 0; j < randomSizeList; ++j) {
            int randomKey = rand() % 100; // Key ngẫu nhiên từ 0-99
            Insert(randomKey, "Value");
        }
    }
}