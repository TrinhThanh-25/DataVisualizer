#include "../inc/HashTable/animation/Presentation.h"

Presentation::Presentation(Font fontNumber, Font fontText, float speed, HashTable& table)
    : fontNumber(fontNumber), fontText(fontText), speed(speed), table(table) {}

void Presentation::InsertNodeAnimation(int key, Node* newNode) {
    int bucket = key % table.GetSize();
    
    // Duyệt qua các node trong bucket để tạo animation tuần tự
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;

    // Bước 1: Highlight lần lượt từng node trong bucket
    while (current != newNode && current != nullptr) {
        SetofAnimation set(fontNumber, fontText, speed);
        Animation highlight(fontNumber, fontText, speed, current);
        highlight.type = 1; // Highlight (đổi màu đỏ rồi về đen)
        set.AddAnimation(highlight);
        SetAnimations.push_back(set); // Thêm set để thực thi tuần tự
        prev = current;
        current = current->next;
    }

    // Bước 2: Fade in node mới (node 40)
    SetofAnimation fadeInSet(fontNumber, fontText, speed);
    Animation fadeIn(fontNumber, fontText, speed, newNode);
    fadeIn.type = 2; // Fade in
    fadeInSet.AddAnimation(fadeIn);
    SetAnimations.push_back(fadeInSet);

    // Bước 3: Vẽ mũi tên từ node trước đó (node 30) đến node mới (node 40)
    if (prev) {
        SetofAnimation edgeSet(fontNumber, fontText, speed);
        Animation edge(fontNumber, fontText, speed, prev);
        edge.type = 6; // Vẽ mũi tên
        edgeSet.AddAnimation(edge);
        SetAnimations.push_back(edgeSet);
    }
}
void Presentation::DeleteNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;

    while (current != nullptr && current->data != key) {
        prev = current;
        current = current->next;
    }

    if (current) {
        SetofAnimation set(fontNumber, fontText, speed);
        Animation highlight(fontNumber, fontText, speed, current);
        highlight.type = 1;
        set.AddAnimation(highlight);

        if (prev && current->next) {
            Animation edge(fontNumber, fontText, speed, prev);
            edge.type = 7;
            set.AddAnimation(edge);
        }

        Animation fadeOut(fontNumber, fontText, speed, current);
        fadeOut.type = 3;
        set.AddAnimation(fadeOut);

        if (current->next) {
            Animation move(fontNumber, fontText, speed, current->next, current->position);
            move.type = 4;
            set.AddAnimation(move);
        }

        SetAnimations.push_back(set);
    }
}

void Presentation::FindNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);

    while (current != nullptr) {
        SetofAnimation set(fontNumber, fontText, speed);
        Animation highlight(fontNumber, fontText, speed, current);
        highlight.type = 1;
        set.AddAnimation(highlight);
        SetAnimations.push_back(set);
        if (current->data == key) break;
        current = current->next;
    }
}

void Presentation::CreateTableAnimation(int size) {
    for (int i = 0; i < size; i++) {
        Node* current = table.getTable(i);
        while (current != nullptr) {
            SetofAnimation set(fontNumber, fontText, speed);
            Animation fadeIn(fontNumber, fontText, speed, current);
            fadeIn.type = 2;
            set.AddAnimation(fadeIn);
            SetAnimations.push_back(set);
            current = current->next;
        }
    }
}

bool Presentation::DrawPresentation() {
    if (SetAnimations.empty()) return true;

    // Chỉ vẽ SetofAnimation đầu tiên
    if (SetAnimations[0].Draw()) {
        // Nếu set đầu tiên hoàn tất, xóa nó
        SetAnimations.erase(SetAnimations.begin());
    }

    // Trả về true nếu không còn set nào
    return SetAnimations.empty();
}

void Presentation::clear() {
    SetAnimations.clear();
}