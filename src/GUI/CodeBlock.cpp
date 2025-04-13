#include <GUI/CodeBlock.h>

CodeBlock::CodeBlock(){}

void CodeBlock::update(){

}

void CodeBlock::draw(){
    if(code!=""){   
        DrawRectangleRec(codeBlockRec,buttonNormal);
        DrawRectangleLinesEx(codeBlockRec,3,outlineButtonColor);
    }
    drawHighlight(codeBlockFontSize);
    drawCode(codePosition.x,codePosition.y,codeBlockFontSize);
}

void CodeBlock::setCode(std::string code){
    this->code=code;
}

void CodeBlock::clearCode(){
    this->code="";
}

void CodeBlock::drawCode( int x, int y, int fontSize){
    std::stringstream stream(code);
    std::string line;
    int lineDis=fontSize+5;
    int pos=0;
    while(std::getline(stream,line)){
        DrawText(line.c_str(),x,y+pos+5.0f,fontSize,codeBlockTextColor);
        pos+=lineDis;
    }
}

void CodeBlock::setHighlight(std::vector<int> ID){
    highlightID=ID;
}

void CodeBlock::drawHighlight(int fontSize){
    for (int x : highlightID){
        DrawRectangle(codeBlockRec.x,codeBlockRec.y+x*(fontSize+5)+2.5f,codeBlockRec.width,fontSize+5.0f,codeBlockHighlightColor);
    }
}

void CodeBlock::clearHighlight(){
    highlightID.clear();
}

CodeBlock CodeBlock::clone() const {
    CodeBlock newCodeBlock;
    newCodeBlock.code = this->code;
    newCodeBlock.highlightID=this->highlightID;
    return newCodeBlock;
}