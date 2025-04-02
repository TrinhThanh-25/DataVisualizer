#pragma once


#include "Animation.h"
#include <vector>

class SetofAnimation {
public:
    Font fontNumber;
    Font fontText;
    float speed;
    std::vector<Animation> animations;

    SetofAnimation(Font fontNumber, Font fontText, float speed);
    void AddAnimation(Animation animation);
    bool Draw();
};