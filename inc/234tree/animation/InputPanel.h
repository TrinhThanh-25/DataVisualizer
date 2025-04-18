#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include "raylib.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "GUI/ColorTheme.h"
#include <vector>
#include <tinyfiledialogs.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

class InputPanel {
private:
    Vector2 position; // Vị trí của panel
    Vector2 size; // Kích thước của panel
    bool isOpen; // Trạng thái mở/đóng của panel
    Button toggleButton; // Nút bấm hình tam giác để mở/đóng
    std::vector<Button> buttons; // Các nút chức năng (Create, Search, Insert, Remove)
    InputBox inputBox; // Ô nhập liệu
    Button goButton; // Nút "Go"

    Button inputFileButton;
    std::vector<std::vector<int>> fileValues2D;
    std::vector<std::vector<int>> LoadFile(const std::string & filepath);

    Color panelColor; // Màu nền của panel
    bool showInputBox; // Trạng thái hiển thị của inputBox và nút Go
    int activeButtonIndex; // Lưu nút nào đang được chọn để hiển thị inputBox (-1 nếu không có)
    int lastInputValue; // Lưu giá trị số đã nhập sau khi nhấn "Go"

public:
    InputPanel(Vector2 pos, Vector2 panelSize);
    void SetPosition(Vector2 pos);
    void Update();
    void Draw();
    int GetInputText();
    int GetActiveButtonIndex() const; // Thêm hàm để lấy activeButtonIndex
    void ResetInputState(); // Thêm hàm để reset trạng thái
    bool IsCreatePressed();
    bool IsSearchPressed();
    bool IsInsertPressed();
    bool IsRemovePressed();

    std::vector<std::vector<int>> GetFileValues2D() const;
    bool IsLoadFilePressed();
};

#endif // INPUTPANEL_H