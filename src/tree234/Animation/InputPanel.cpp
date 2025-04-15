#include <234tree/animation/InputPanel.h>
#include <cstdlib> // Để dùng std::stoi

InputPanel::InputPanel(Vector2 pos, Vector2 panelSize, Color panelCol)
    : position(pos), size(panelSize), panelColor(panelCol), inputBox(pos.x + 10, pos.y + 10, 80, 30, 10, WHITE, BLACK) {
    isOpen = true; // Mặc định panel mở
    showInputBox = false; // Ban đầu không hiển thị inputBox
    activeButtonIndex = -1; // Không có nút nào được chọn
    lastInputValue = -1; // Giá trị mặc định ban đầu

    // Thiết lập nút bấm hình tam giác (toggle button)
    toggleButton.setPosition({pos.x - 20, pos.y + panelSize.y / 2});
    toggleButton.setSize({30, panelSize.y});
    toggleButton.setText("", 0); // Không có text, sẽ vẽ hình tam giác
    toggleButton.setColor(GRAY, DARKGRAY, DARKGRAY);
    toggleButton.setRectangle();

    // Thiết lập các nút chức năng (Create, Search, Insert, Remove)
    const char* buttonLabels[] = {"Create(M,N)", "Search(v)", "Insert(v)", "Remove(v)"};
    for (int i = 0; i < 4; i++) {
        Button btn;
        btn.setPosition({pos.x + size.x / 2, pos.y + 20 + i * 40}); // Căn giữa theo chiều ngang
        btn.setSize({size.x - 20, 30});
        btn.setText(buttonLabels[i], 20);
        btn.setColor(LIGHTGRAY, GRAY, DARKGRAY);
        btn.setRectangle();
        buttons.push_back(btn);
    }

    // Thiết lập nút "Go" (ban đầu không hiển thị, sẽ cập nhật vị trí sau)
    goButton.setSize({30, 30});
    goButton.setText("Go", 20);
    goButton.setColor(LIGHTGRAY, GRAY, DARKGRAY);
}

void InputPanel::SetPosition(Vector2 pos) {
    position = pos;

    // Cập nhật vị trí của nút toggle
    toggleButton.setPosition({pos.x - 20, pos.y + size.y / 2});
    toggleButton.setRectangle();

    // Cập nhật vị trí của các nút chức năng
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].setPosition({pos.x + size.x / 2, pos.y + 20 + i * 40}); // Căn giữa theo chiều ngang
        buttons[i].setRectangle();
    }

    // Cập nhật vị trí của ô nhập liệu và nút "Go" nếu đang hiển thị
    if (showInputBox && activeButtonIndex != -1) {
        Vector2 btnPos = buttons[activeButtonIndex].getPosition();
        inputBox = InputBox(btnPos.x + (size.x - 20) / 2 + 10, btnPos.y, 80, 30, 10, WHITE, BLACK);
        goButton.setPosition({btnPos.x + (size.x - 20) / 2 + 100, btnPos.y});
        goButton.setRectangle();
    }
}

void InputPanel::Update() {
    // Cập nhật trạng thái của nút toggle
    toggleButton.update();
    if (toggleButton.isPressed()) {
        isOpen = !isOpen;
        if (!isOpen) {
            showInputBox = false; // Ẩn inputBox khi đóng panel
            activeButtonIndex = -1;
            lastInputValue = -1; // Reset giá trị đã nhập
        }
    }

    // Chỉ cập nhật các thành phần bên trong panel nếu panel đang mở
    if (isOpen) {
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].update();
            if (buttons[i].isPressed()) {
                // Khi một nút chức năng được nhấn, hiển thị inputBox kế bên nút đó
                showInputBox = true;
                activeButtonIndex = i;
                Vector2 btnPos = buttons[i].getPosition();
                inputBox = InputBox(btnPos.x + (size.x - 20) / 2 + 10, btnPos.y, 80, 30, 10, WHITE, BLACK);
                goButton.setPosition({btnPos.x + (size.x - 20) / 2 + 100, btnPos.y});
                goButton.setRectangle();
            }
        }

        if (showInputBox) {
            inputBox.Update();
            goButton.update();
        }
    }
}

void InputPanel::Draw() {
    // Vẽ nút toggle (hình tam giác)
    Vector2 togglePos = toggleButton.getPosition();
    if (isOpen) {
        // Tam giác chỉ về bên trái (panel mở)
        DrawTriangle(
            {togglePos.x - 5, togglePos.y - 5},
            {togglePos.x - 5, togglePos.y + 5},
            {togglePos.x + 5, togglePos.y},
            toggleButton.isHovered() ? GRAY : DARKGRAY
        );
        
    } else {
        // Tam giác chỉ về bên phải (panel đóng)
        DrawTriangle(
            {togglePos.x + 5, togglePos.y - 5},
            {togglePos.x + 5, togglePos.y + 5},
            {togglePos.x - 5, togglePos.y},
            toggleButton.isHovered() ? GRAY : DARKGRAY
        );
    }

    // Chỉ vẽ panel nếu đang mở
    if (isOpen) {
        // Vẽ nền của panel
        DrawRectangle(position.x, position.y, size.x, size.y, panelColor);

        // Vẽ các nút chức năng
        for (auto& btn : buttons) {
            btn.drawRectangleRounded(0.2f);
            btn.drawText(BLACK);
        }

        // Vẽ ô nhập liệu và nút "Go" nếu đang hiển thị
        if (showInputBox) {
            inputBox.Draw();
            goButton.drawRectangleRounded(0.2f);
            goButton.drawText(BLACK);
        }
    }
}

int InputPanel::GetInputText() {
    if (showInputBox && goButton.isPressed()) {
        std::string input = inputBox.GetText();
        if (input.empty()) {
            lastInputValue = -1; // Trả về -1 nếu ô nhập rỗng
        } else {
            try {
                size_t pos;
                lastInputValue = std::stoi(input, &pos);
                // Kiểm tra xem toàn bộ chuỗi đã được chuyển đổi thành số chưa
                if (pos != input.length()) {
                    lastInputValue = -1; // Trả về -1 nếu chuỗi không phải số hợp lệ
                }
            } catch (...) {
                lastInputValue = -1; // Trả về -1 nếu có lỗi (ví dụ: chuỗi không phải số)
            }
        }
        return lastInputValue;
    }
    return -1; // Trả về -1 nếu không có giá trị mới
}

int InputPanel::GetActiveButtonIndex() const {
    return activeButtonIndex;
}

void InputPanel::ResetInputState() {
    showInputBox = false;
    activeButtonIndex = -1;
    lastInputValue = -1;
}

bool InputPanel::IsCreatePressed() {
    return activeButtonIndex == 0 && lastInputValue != -1;
}

bool InputPanel::IsSearchPressed() {
    return activeButtonIndex == 1 && lastInputValue != -1;
}

bool InputPanel::IsInsertPressed() {
    return activeButtonIndex == 2 && lastInputValue != -1;
}

bool InputPanel::IsRemovePressed() {
    return activeButtonIndex == 3 && lastInputValue != -1;
}