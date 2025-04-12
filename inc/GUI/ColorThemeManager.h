#ifndef COLORTHEMEMANAGER_H
#define COLORTHEMEMANAGER_H

#include <raylib.h>
#include <GUI/Button.h>
#include <GUI/ColorTheme.h>

enum class StyleTheme {
    DEF, SUNNY, RLTECH, LAVANDA, ENEFETE, DARK, CYBER, CANDY, TERMINAL, BLUISH
};

class ColorThemeManager {
public:
    ColorThemeManager();

    void setColorTheme();
    void applyTheme(ColorTheme theme);
    void update();
    void draw();
public:
    bool isTheme = false;
    bool isUpdate = true;
private:
    Button settingTheme;
    StyleTheme currentTheme;
    Rectangle panel;
    Button def;
    Button sunny;
    Button rltech;
    Button lavanda;
    Button enefete;
    Button dark;
    Button cyber;
    Button candy;
    Button terminal;
    Button bluish;
};

#endif