#include "SetofAnimation.h"

SetofAnimation::SetofAnimation(Font fontNumber, Font fontText, float speed)
    : fontNumber(fontNumber), fontText(fontText), speed(speed) {}

void SetofAnimation::AddAnimation(Animation animation) {
    animations.push_back(animation);
}

bool SetofAnimation::Draw() {
    if (animations.empty()) return true;
    bool isComplete = true;
    for (int i = 0; i < animations.size(); i++) {
        if (!animations[i].DrawAnimation()) {
            isComplete = false;
        }
    }
    if (isComplete) animations.clear();
    return isComplete;
}