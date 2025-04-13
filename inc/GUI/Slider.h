#pragma once
#include "raylib.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <GUI/Resources.h>

class Slider{
    public:
        Rectangle box;
        Rectangle sliderRect;
        Vector2 position;
        float width, height;
        float minVal, maxVal;
        float val;
        Vector2 knobSize;
        bool isDragging;
        int numSteps;

        Slider(float minVal, float maxVal, float initialVal, int steps);
        void Update();
        void Draw();

        void reset();
};