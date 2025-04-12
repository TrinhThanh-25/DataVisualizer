#include <GUI/CodeBlock.h>

CodeBlock::CodeBlock(){}

void CodeBlock::update(){

}

void CodeBlock::draw(){
    if(code!=""){
        DrawRectangle(1200,700,400,200,dataTitleColor);
        DrawRectangleLinesEx({1200,700,400,200},3,outlineButtonColor);
    }
    drawHighlight(16);
    drawCode(1215,700,16);
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
        DrawText(line.c_str(),x,y+pos+2.5f,fontSize,codeBlockTextColor);
        pos+=lineDis;
    }
}

void CodeBlock::setHighlight(std::vector<int> ID){
    highlightID=ID;
}

void CodeBlock::drawHighlight(int fontSize){
    for (int x : highlightID){
        DrawRectangle(1200,700+x*(fontSize+5),400,fontSize+5.0f,codeBlockHighlightColor);
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