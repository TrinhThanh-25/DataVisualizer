#include "GUI/CodeBlock.h"
#include <string>

CodeBlock::CodeBlock() : highlightColor(highlightColor){}

void CodeBlock::loadCode(const char* text){
    if(text==this->text){
        return;
    }
    this->text=text;
    highlightBlock.clear();
    std::vector<Vector2>().swap(linePosition);
    getLinePosition();
}

void CodeBlock::setHighLight(const std::vector<int>& lineID){
    highlightBlock.clear();
    for (int id : lineID){
        if(id<0||id>=linePosition.size())
            continue;
        highlightBlock[id] = {linePosition[id].x,linePosition[id].y,500,25};
    }
}

void CodeBlock::draw(){
    for (auto block : highlightBlock)
        DrawRectangleRounded(block.second,0,0,highlightColor);
        DrawText(text,0,0,18,BLACK);
}

void CodeBlock::getLinePosition() {
    std::string text = text;
    for (int i = 0; i < text.size(); ++i)
        if (i == 0 || text[i - 1] == '\n') {
            linePosition.push_back({0, 0});
        }
}
