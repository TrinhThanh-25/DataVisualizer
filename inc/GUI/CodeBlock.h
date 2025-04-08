#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <vector>
#include <string>
#include <sstream>
#include <GUI/Resources.h>

class CodeBlock{
    public:
        CodeBlock();
        void update();
        void draw();

        void setCode(std::string code);
        void clearCode();
        void drawCode(int x, int y, int fontSize, Color color);

        void setHighlight(std::vector<int> ID);
        void drawHighlight(int fontSize);
        void clearHighlight();

        CodeBlock clone() const;
    private:
        Color background=LIGHTGRAY;
        Color highlight=YELLOW;
        std::string code;
        std::vector<int> highlightID;
};

#endif