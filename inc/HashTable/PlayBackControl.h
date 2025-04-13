#pragma once
#include "raylib.h"
#include "GUI/Slider.h"
#include "GUI/Button.h"
#include <vector>
#include "HashTable.h"

class PlaybackControl {
public:
    PlaybackControl(Vector2 position, float width, float height);

    void Update(int& currentPresentationIndex, int& currentStateIndex, 
                std::vector<std::vector<HashTable>> historyState);
    void Draw();
    bool IsPlaying() const;

private:
    Vector2 position;
    float width;
    float height;

    Slider historySlider;
    Button skipBackButton;
    Button stepBackButton;
    Button stepNextButton;
    Button skipNextButton;

    bool isPlaying;
};