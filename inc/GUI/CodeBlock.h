#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include "GUI/Resources.h"
#include <map>
#include <vector>

class CodeBlock{
    public:
        CodeBlock();
        void loadCode(const char* text);
        void setHighLight(const std::vector<int>& lineID);
        void draw();
        void getLinePosition();

    private:
        const Color highlightColor;
        const char* text="";
        std::map<int, Rectangle> highlightBlock;
        std::vector<Vector2> linePosition;
};

#endif