#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include "raylib.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <vector>
#include <GUI/Resources.h>
#include <GUI/Panel.h>
=======
#include "GUI/ColorTheme.h"
#include <vector>
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
#include <vector>
#include <GUI/Resources.h>
#include <GUI/Panel.h>
>>>>>>> 50f6135 (Merge file)
=======
#include "GUI/ColorTheme.h"
#include <vector>
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
#include "GUI/ColorTheme.h"
#include <vector>
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
#include <tinyfiledialogs.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
class InputPanel : public Panel {
private:
=======
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
class InputPanel {
private:
    Vector2 position; // Vị trí của panel
    Vector2 size; // Kích thước của panel
    bool isOpen; // Trạng thái mở/đóng của panel
    Button toggleButton; // Nút bấm hình tam giác để mở/đóng
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
class InputPanel : public Panel {
private:
>>>>>>> 50f6135 (Merge file)
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    std::vector<Button> buttons; // Các nút chức năng (Create, Search, Insert, Remove)
    InputBox inputBox; // Ô nhập liệu
    Button goButton; // Nút "Go"

    Button inputFileButton;
    std::vector<std::vector<int>> fileValues2D;
    std::vector<std::vector<int>> LoadFile(const std::string & filepath);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

    Color panelColor; // Màu nền của panel
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> 50f6135 (Merge file)
=======

    Color panelColor; // Màu nền của panel
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======

    Color panelColor; // Màu nền của panel
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    bool showInputBox; // Trạng thái hiển thị của inputBox và nút Go
    int activeButtonIndex; // Lưu nút nào đang được chọn để hiển thị inputBox (-1 nếu không có)
    int lastInputValue; // Lưu giá trị số đã nhập sau khi nhấn "Go"

public:
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    InputPanel();
    void update() override;
    void draw() override;
=======
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    InputPanel(Vector2 pos, Vector2 panelSize);
    void SetPosition(Vector2 pos);
    void Update();
    void Draw();
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
    InputPanel();
    void update() override;
    void draw() override;
>>>>>>> 50f6135 (Merge file)
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
    int GetInputText();
    int GetActiveButtonIndex() const; // Thêm hàm để lấy activeButtonIndex
    void ResetInputState(); // Thêm hàm để reset trạng thái
    bool IsCreatePressed();
    bool IsSearchPressed();
    bool IsInsertPressed();
    bool IsRemovePressed();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    bool isAnyButtonPressed() override;
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
    bool isAnyButtonPressed() override;
>>>>>>> 50f6135 (Merge file)
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
=======
>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43

    std::vector<std::vector<int>> GetFileValues2D() const;
    bool IsLoadFilePressed();
};

#endif // INPUTPANEL_H