#include <GUI/ColorThemeManager.h>

ColorThemeManager::ColorThemeManager() {
    currentTheme = StyleTheme::DEF;
    setColorTheme();

    panel={500,250,600,300};

    settingTheme.setSize({50, 50});
    settingTheme.setPosition({1600-15-25,15+25});

    def.setSize({80, 80});
    sunny.setSize({80, 80});
    rltech.setSize({80, 80});
    lavanda.setSize({80, 80});
    enefete.setSize({80, 80});
    dark.setSize({80, 80});
    cyber.setSize({80, 80});
    candy.setSize({80, 80});
    terminal.setSize({80, 80});
    bluish.setSize({80, 80});
    def.setPosition({570,365});
    sunny.setPosition({685,365});
    rltech.setPosition({800,365});
    lavanda.setPosition({915,365});
    enefete.setPosition({1030,365});
    dark.setPosition({570,480});
    cyber.setPosition({685,480});
    candy.setPosition({800,480});
    terminal.setPosition({915,480});
    bluish.setPosition({1030,480});
}

void ColorThemeManager::setColorTheme(){
    switch (currentTheme) {
        case StyleTheme::DEF:
            applyTheme(Default);
            break;
        case StyleTheme::SUNNY:
            applyTheme(Sunny);
            break;
        case StyleTheme::RLTECH:
            applyTheme(RLTech);
            break;
        case StyleTheme::LAVANDA:
            applyTheme(Lavanda);
            break;
        case StyleTheme::ENEFETE:
            applyTheme(EneFete);
            break;
        case StyleTheme::DARK:
            applyTheme(Dark);
            break;
        case StyleTheme::CYBER:
            applyTheme(Cyber);
            break;
        case StyleTheme::CANDY:
            applyTheme(Candy);
            break;
        case StyleTheme::TERMINAL:
            applyTheme(Terminal);
            break;
        case StyleTheme::BLUISH:
            applyTheme(Bluish);
            break;
        default:
            break;
    }
}

void ColorThemeManager::applyTheme(ColorTheme theme) {
    isUpdate = false;
    appTitleColor = theme.appTitleColor;
    backgroundColor = theme.backgroundColor;

    dataTitleColor = theme.dataTitleColor;
    dataTitleTextColor = theme.dataTitleTextColor;
    buttonNormal = theme.buttonNormal;
    buttonHovered = theme.buttonHovered;
    buttonPressed = theme.buttonPressed;
    textButtonNormal = theme.textButtonNormal;
    textButtonHovered = theme.textButtonHovered;
    textButtonPressed = theme.textButtonPressed;
    outlineButtonColor = theme.outlineButtonColor;
    outlineButtonHoveredColor = theme.outlineButtonHoveredColor;
    outlineButtonPressedColor = theme.outlineButtonPressedColor;

    codeBlockTextColor = theme.codeBlockTextColor;
    codeBlockHighlightColor = theme.codeBlockHighlightColor;
    
    nodeColor = theme.nodeColor;
    nodeTextColor = theme.nodeTextColor;

    nodeHighlightColor = theme.nodeHighlightColor;
    nodeHighlightTextColor = theme.nodeHighlightTextColor;

    nodeCostColor = theme.nodeCostColor;
    nodeKnownColor = theme.nodeKnownColor;
    nodeKnownTextColor = theme.nodeKnownTextColor;
    lineColor = theme.lineColor;
    lineTextColor = theme.lineTextColor;

    boxColor = theme.boxColor;
    boxTextColor = theme.boxTextColor;
}

void ColorThemeManager::update() {
    settingTheme.update();
    if(settingTheme.isPressed()||(isTheme && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!CheckCollisionPointRec(GetMousePosition(), panel))){
        isTheme = !isTheme;
    }
    if(isTheme){
        def.update(Default);
        sunny.update(Sunny);
        rltech.update(RLTech);
        lavanda.update(Lavanda);
        enefete.update(EneFete);
        dark.update(Dark);
        cyber.update(Cyber);
        candy.update(Candy);
        terminal.update(Terminal);
        bluish.update(Bluish);

        if(def.isPressed()){
            currentTheme = StyleTheme::DEF;
            setColorTheme();
        }
        if(sunny.isPressed()){
            currentTheme = StyleTheme::SUNNY;
            setColorTheme();
        }
        if(rltech.isPressed()){
            currentTheme = StyleTheme::RLTECH;
            setColorTheme();
        }
        if(lavanda.isPressed()){
            currentTheme = StyleTheme::LAVANDA;
            setColorTheme();
        }
        if(enefete.isPressed()){
            currentTheme = StyleTheme::ENEFETE;
            setColorTheme();
        }
        if(dark.isPressed()){
            currentTheme = StyleTheme::DARK;
            setColorTheme();
        }
        if(cyber.isPressed()){
            currentTheme = StyleTheme::CYBER;
            setColorTheme();
        }
        if(candy.isPressed()){
            currentTheme = StyleTheme::CANDY;
            setColorTheme();
        }
        if(terminal.isPressed()){
            currentTheme = StyleTheme::TERMINAL;
            setColorTheme();
        }
        if(bluish.isPressed()){
            currentTheme = StyleTheme::BLUISH;
            setColorTheme();
        }
    }
}

void ColorThemeManager::draw(){
    if(isTheme){
        DrawRectangle(0,0,1600,900,Fade(BLACK,0.5f));
        DrawRectangleRounded(panel, 0, 0, buttonNormal); 
        DrawRectangleRoundedLinesEx(panel, 0, 0, 1, BLACK);
        DrawText("Theme", 800-MeasureText("Theme",30)/2.0f, 290-15 , 30, textButtonNormal);
        def.drawRectangleRounded(0);
        sunny.drawRectangleRounded(0);
        rltech.drawRectangleRounded(0);
        lavanda.drawRectangleRounded(0);
        enefete.drawRectangleRounded(0);
        dark.drawRectangleRounded(0);
        cyber.drawRectangleRounded(0);
        candy.drawRectangleRounded(0);
        terminal.drawRectangleRounded(0);
        bluish.drawRectangleRounded(0);
        def.drawOutlineRounded(0, 0, 5);
        sunny.drawOutlineRounded(0, 0, 5);
        rltech.drawOutlineRounded(0, 0, 5);
        lavanda.drawOutlineRounded(0, 0, 5);
        enefete.drawOutlineRounded(0, 0, 5);
        dark.drawOutlineRounded(0, 0, 5);
        cyber.drawOutlineRounded(0, 0, 5);
        candy.drawOutlineRounded(0, 0, 5);
        terminal.drawOutlineRounded(0, 0, 5);
        bluish.drawOutlineRounded(0, 0, 5);
    }
    settingTheme.drawRectangleRounded(100);
    settingTheme.drawOutlineRounded(100, 0, 3);
}

//Menu
Color appTitleColor({BLACK});
Color backgroundColor({WHITE});

//Panel
Color dataTitleColor({185,185,185,255});
Color dataTitleTextColor({BLACK});
Color buttonNormal({161,161,161,255});
Color buttonHovered({133,133,133,255});
Color buttonPressed({110,110,110,255});
Color textButtonNormal({BLACK});
Color textButtonHovered({BLACK});
Color textButtonPressed({BLACK});
Color outlineButtonColor({0,0,0,255});
Color outlineButtonHoveredColor({0,0,0,255});
Color outlineButtonPressedColor({0,0,0,255});

//CodeBlock
Color codeBlockTextColor({0,0,0,255});
Color codeBlockHighlightColor({255,253,85,255});

//Data
Color nodeColor({0,0,0,255});
Color nodeTextColor({255,255,255,255});

Color nodeHighlightColor({255,0,0,255});
Color nodeHighlightTextColor({255,255,255,255});

//Shortest Path
Color nodeCostColor({0,0,0,255});
Color nodeKnownColor({0,255,0,255});
Color nodeKnownTextColor({0,0,0,255});
Color lineColor({0,0,255,255});
Color lineTextColor({0,0,0,255});

Color boxColor({LIGHTGRAY});
Color boxTextColor({BLACK});