#include <234tree/animation/InputPanel.h>
#include <cstdlib> // Để dùng std::stoi
#include <iostream>

InputPanel::InputPanel()
    : inputBox(120,680,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor) {
    activeButtonIndex = -1; // Không có nút nào được chọn
    lastInputValue = -1; // Giá trị mặc định ban đầu
    // Thiết lập các nút chức năng (Create, Search, Insert, Remove)
    const char* buttonLabels[] = {"Create", "Search", "Insert", "Remove"};
    for (int i = 0; i < 4; i++) {
        Button btn;
        btn.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 650+50*i+(panelButtonSize.y/2.0f)}); // Căn giữa theo chiều ngang
        btn.setSize(panelButtonSize);
        btn.setText(buttonLabels[i], panelButtonFontSize);

        inputFileButton.setPosition({320,740});
        inputFileButton.setSize({120, 30});
        inputFileButton.setText("Load File",SLLButtonFontSize);
        // btn.setColor(LIGHTGRAY, GRAY, DARKGRAY);
        // btn.setRectangle();
        buttons.push_back(btn);
    }

    // Thiết lập nút "Go" (ban đầu không hiển thị, sẽ cập nhật vị trí sau)
    goButton.setSize({260, 30});
    goButton.setText("Apply",SLLButtonFontSize);
    goButton.setPosition({250,780});
    //goButton.setColor(LIGHTGRAY, GRAY, DARKGRAY);
}

void InputPanel::update() {
    updatePanel(); // Cập nhật trạng thái của panel
    // Chỉ cập nhật các thành phần bên trong panel nếu panel đang mở
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].update();
        if (buttons[i].isPressed()) {
            // Khi một nút chức năng được nhấn, hiển thị inputBox kế bên nút đó
            activeButtonIndex = i;
            if(isUsing&&isUsing==&buttons[i]) {
                isUsing->deSelected();
                isUsing=nullptr;
            }
            else{
                buttons[i].Selected();
                if(isUsing&&isUsing!=&buttons[i]) this->isUsing->deSelected();
                this->isUsing = &buttons[i];
            }
            //goButton.setRectangle();
        }
        if(&buttons[i]==isUsing){
            activeButtonIndex = i;
        }
    }

    if (isUsing) {
        inputBox.Update();
        goButton.update();
        inputFileButton.update();
        if(inputFileButton.isPressed()){
            static const char* filters[] = {"*.txt"};
            const char * filepath = tinyfd_openFileDialog("Choose file", "", 1,filters, "Text file", 0);
            if(filepath){
                fileValues2D = LoadFile(filepath);
                lastInputValue = -1;
            }
            else{
                fileValues2D.clear();
                lastInputValue = -1;
            }
        }
    }
}


void InputPanel::draw() {
    drawPanel();
    // Vẽ các nút chức năng
    for (auto& btn : buttons) {
        btn.drawRectangleRounded(100);
        btn.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút
        btn.drawText();
    }

    // Vẽ ô nhập liệu và nút "Go" nếu đang hiển thị
    if (isUsing) {
        inputBox.Draw();
        goButton.drawRectangleRounded(100);
        goButton.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút "Go"
        goButton.drawText();

        inputFileButton.drawRectangleRounded(100);
        inputFileButton.drawText();
        inputFileButton.drawOutlineRounded(100, 0, 3);
    }
}


int InputPanel::GetInputText() {
    if (isUsing && goButton.isPressed()) {
        std::string input = inputBox.GetText();
        inputBox.clearText(); // Xóa nội dung ô nhập sau khi nhấn "Go"
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

std::vector<std::vector<int>> InputPanel::LoadFile(const std::string & filepath) {
    std::vector<std::vector<int>> values;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Không thể mở file: " << filepath << std::endl;
        return values;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> lineValues;
        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            try {
                size_t pos;
                int intValue = std::stoi(value, &pos);
                if (pos == value.length()) {
                    lineValues.push_back(intValue);
                } else {
                    std::cout << "Giá trị không hợp lệ (không phải số nguyên đầy đủ): " << value << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Lỗi chuyển đổi giá trị: " << value << " - " << e.what() << std::endl;
            }
        }
        if (!lineValues.empty()) {
            values.push_back(lineValues);
        }
    }

    file.close();
    if (values.empty()) {
        std::cout << "File rỗng hoặc không chứa số hợp lệ: " << filepath << std::endl;
    } else {
        std::cout << "Đọc thành công từ file: " << filepath << std::endl;
        for (const auto& row : values) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    return values;
}


std::vector<std::vector<int>> InputPanel::GetFileValues2D() const{
    return fileValues2D;
}


int InputPanel::GetActiveButtonIndex() const {
    return activeButtonIndex;
}

void InputPanel::ResetInputState() {
    activeButtonIndex = -1;
    lastInputValue = -1;
    fileValues2D.clear();
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

bool InputPanel::isAnyButtonPressed() {
    for (auto & btn : buttons) {
        if (btn.isPressed()) {
            return true; // Nếu bất kỳ nút nào được nhấn, trả về true
        }
    }
    return false; // Nếu không có nút nào được nhấn, trả về false
}

bool InputPanel::IsLoadFilePressed(){
    return (activeButtonIndex >= 0 && activeButtonIndex <= 3) && !fileValues2D.empty();
}