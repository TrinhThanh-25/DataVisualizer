#ifndef HASHTABLEVISUALIZATION_H
#define HASHTABLEVISUALIZATION_H
#include "raylib.h"
#include "raymath.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "HashTable.h"
#include "animation/Presentation.h"

#define MAX_TABLE_SIZE 10
#define HASH_TABLE_WIDTH 800
#define HASH_TABLE_HEIGHT 600
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30

class HashTableVisualization {
public:
    HashTableVisualization(const Texture2D& hollowCircle, const Texture2D& solidCircle, const Texture2D& arrowEdge, const Font& fontNumber, const Font& fontText, const bool& isLightMode, const float& speed);
    ~HashTableVisualization();

    void Init(int size);
    void Insert(int key);
    void Delete(int key);
    bool Find(int key);
    void Draw();
    void HandleInput();
    void HandleMouseInput();

private:
    HashTable hashTable;
    Button insertButton;
    Button deleteButton;
    Button findButton;
    Button initButton;
    InputBox inputBox;
    Presentation presentations;

    const Texture2D hollowCircle;
    const Texture2D solidCircle;
    const Texture2D arrowEdge;
    const Font fontNumber;
    const Font fontText;
    const bool isLightMode;
    const float speed;

    bool isInserting;
    bool isDeleting;
    bool isFinding;
    bool isInitializing;

    void DrawHashTable();
    void DrawNode(Node* node);
    void DrawLine(Vector2 start, Vector2 end);
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawLink(Vector2 start, Vector2 end);
};
#endif