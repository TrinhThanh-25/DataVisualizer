#include "../inc/HashTable/Slider.h"

void Slider::ToggleMode(){
    isSmooth = !isSmooth;
    return;
}

void Slider::Update(){
    Vector2 mousePos = GetMousePosition();
    
    // Định nghĩa vùng của thanh trượt
    Rectangle sliderRect = {position.x, position.y - height / 2, width, height * 2}; // Mở rộng vùng nhấn cho dễ thao tác

    // Kiểm tra nếu người dùng nhấn chuột trái vào nút kéo
    Rectangle knobRect = {position.x + (val - minVal) / (maxVal - minVal) * (width - knobSize.x), 
                            position.y - knobSize.y / 2, knobSize.x, knobSize.y};

    // Kiểm tra nhấn trực tiếp vào thanh trượt
    if (CheckCollisionPointRec(mousePos, sliderRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float newX = mousePos.x - position.x;
        newX = std::max(0.0f, std::min(newX, width - knobSize.x)); // Giới hạn trong thanh trượt

        if (isSmooth) {
            // Chế độ mượt mà: giá trị thay đổi liên tục
            val = minVal + (newX / (width - knobSize.x)) * (maxVal - minVal);
        } else {
            // Chế độ chia phần: giá trị chỉ nhận các bước cố định
            float stepSize = (maxVal - minVal) / (numSteps - 1);
            float normalizedValue = (newX / (width - knobSize.x)) * (maxVal - minVal);
            int step = static_cast<int>(std::round(normalizedValue / stepSize));
            val = minVal + step * stepSize;
            val = std::max(minVal, std::min(maxVal, val));
        }
    }

    // Kiểm tra nếu người dùng nhấn chuột trái vào nút kéo để kéo
    if (CheckCollisionPointRec(mousePos, knobRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        isDragging = true;
    }

    // Cập nhật giá trị khi kéo
    if (isDragging) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        } else {
            float newX = mousePos.x - position.x;
            newX = std::max(0.0f, std::min(newX, width - knobSize.x));

            if (isSmooth) {
                val = minVal + (newX / (width - knobSize.x)) * (maxVal - minVal);
            } else {
                float stepSize = (maxVal - minVal) / (numSteps - 1);
                float normalizedValue = (newX / (width - knobSize.x)) * (maxVal - minVal);
                int step = static_cast<int>(std::round(normalizedValue / stepSize));
                val = minVal + step * stepSize;
                val = std::max(minVal, std::min(maxVal, val));
            }
        }
    }
}

void Slider::Draw(){
    DrawRectangle(position.x, position.y, width, height, GRAY);
    
    if (!isSmooth) {
        float stepWidth = (width - knobSize.x) / (numSteps - 1);
        for (int i = 0; i < numSteps; ++i) {
            float x = position.x + i * stepWidth;
            DrawLine(x, position.y - 5, x, position.y + height + 5, BLACK);
        }
    }

    float knobX = position.x + (val - minVal) / (maxVal - minVal) * (width - knobSize.x);
    DrawRectangle(knobX, position.y - knobSize.y / 2, knobSize.x, knobSize.y, DARKGRAY);

    std::string speedText = "Speed: " + std::to_string(val).substr(0, 4);
    std::string modeText = isSmooth ? "Mode: Smooth" : "Mode: Discrete";
    DrawText(speedText.c_str(), position.x, position.y + height + 10, 20, BLACK);
    DrawText(modeText.c_str(), position.x, position.y + height + 35, 20, BLACK);
}

