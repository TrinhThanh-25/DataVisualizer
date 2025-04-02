#pragma once
#include "SetofAnimation.h"
#include "../HashTable.h"
#include <vector>

class Presentation {
public:
    Font fontNumber;
    Font fontText;
    float speed;
    HashTable & table; // Vẫn giữ tham chiếu, nhưng sẽ không gán lại
    std::vector<SetofAnimation> SetAnimations;

    Presentation(Font fontNumber, Font fontText, float speed, HashTable& table);
    void InsertNodeAnimation(int key, Node* newNode);
    void DeleteNodeAnimation(int key);
    void FindNodeAnimation(int key);
    void CreateTableAnimation(int size);
    bool DrawPresentation();
    void clear();
};