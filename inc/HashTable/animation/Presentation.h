#pragma once
#include "SetofAnimation.h"
#include "../HashTable.h"
#include <vector>


class Presentation {
public:
    float &speed;
    HashTable & table; // Vẫn giữ tham chiếu, nhưng sẽ không gán lại
    std::vector<SetofAnimation> SetAnimations;
    //std::vector<SetofAnimation> historyOfSets;
    int currentStep;

    std::vector<std::vector<HashTable>> &historyState;
    int &currentPresentationIndex;
    int &currentStateIndex;
    //int currentIndex;

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> 50f6135 (Merge file)
=======

>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    Presentation(float &speed, HashTable& table, std::vector<std::vector<HashTable>> &historyState, int &currentPresentationIndex, int &currentStateIndex);
    void InsertNodeAnimation(int key, Node* newNode);
    void DeleteNodeAnimation(int key);
    void FindNodeAnimation(int key);
    void CreateTableAnimation(int size);
    bool DrawPresentation();
    void clear();
    //void RewindStep();
};