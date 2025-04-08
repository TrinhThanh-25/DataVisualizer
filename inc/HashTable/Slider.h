#pragma once
#include "raylib.h"
#include <string>
#include <algorithm>
#include <cmath>

class Slider{
    public:
        Vector2 position;
        float width, height;
        float minVal, maxVal;
        float val;
        Vector2 knobSize;
        bool isDragging;
        bool isSmooth;
        int numSteps;

        Slider(Vector2 pos, float w, float h, float minVal, float maxVal, float initialVal, int steps = 10) 
        : position(pos), width(w), height(h), minVal(minVal), maxVal(maxVal), val(initialVal), 
          knobSize({10, h + 10}), isDragging(false), isSmooth(true), numSteps(steps) {}

        void ToggleMode();
        void Update();
        void Draw();
};