#pragma once
#include "SetofAnimation.h"
#include "../HashTable.h"
#include "GUI/CodeBlock.h"
#include "hashtableCode.h"
#include <vector>


class Presentation {
public:
    float &speed;
    HashTable *& table; // Vẫn giữ tham chiếu, nhưng sẽ không gán lại
    std::vector<SetofAnimation> SetAnimations;
    //std::vector<SetofAnimation> historyOfSets;
    int currentStep;

    std::vector<std::vector<HashTable*>> &historyState;
    std::vector<std::vector<int>> &historyCode;
    int &currentPresentationIndex;
    int &currentStateIndex;
    CodeBlock & codeBlock;
    //int currentIndex;

    Presentation(float &speed, HashTable *& table, std::vector<std::vector<HashTable*>> &historyState, std::vector<std::vector<int>> & historyCode, CodeBlock & codeBlock, int &currentPresentationIndex, int &currentStateIndex);
    void InsertNodeAnimation(int key, Node* newNode);
    void DeleteNodeAnimation(int key);
    void FindNodeAnimation(int key);
    void CreateTableAnimation(int size);
    //void UpdateAnimation(int initValue, int finalValue, Node* newNode);
    bool DrawPresentation();
    void clear();
    //void RewindStep();
};