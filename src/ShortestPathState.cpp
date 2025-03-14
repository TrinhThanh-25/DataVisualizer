#include "ShortestPath/ShortestPathState.h"

ShortestPathState::ShortestPathState() : NodesBox(120,650,260,40,20,LIGHTGRAY,BLACK), EdgesBox(120,775,260,40,20,LIGHTGRAY,BLACK), StartNodesBox(120,650,260,40,20,LIGHTGRAY,BLACK){
    this->Random.setText("Random",15);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,710});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",15);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,710});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",15);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,750});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();
}

void ShortestPathState::update(){
    ST.update();
    panel.update();
    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        std::string nodes = getRandomInput(10);
        int numNodes = std::stoi(nodes);
        NodesBox.setText(nodes);
        EdgesBox.setText(getRandomInput(numNodes*(numNodes-1)));
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        if(panel.isCreateUsed()&&NodesBox.GetText()!=""&&EdgesBox.GetText()!=""){
            ST.createGraph(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
        }
        else if(panel.isAddUsed()){
            ST.addEdge(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
        }
        else if(panel.isRemoveUsed()){
            ST.removeEdge(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
        }
        else if(panel.isSearchUsed()){
            ST.searchPath(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
        } 
        resetBox();
    }
    else if(panel.isBackPressed()){
        ST.clearGraph();
        resetBox();
    }
    else if(panel.isAnyButtonPressed()){
        resetBox();
    }
    if(panel.isCreateUsed()){
        NodesBox.Update();
        EdgesBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
}

void ShortestPathState::draw(){
    ST.draw();
    panel.draw();
    DrawText("Shortest Path",800-MeasureText("Shortest Path",24)/2.0f,40-12,24, BLACK);
    STCode.draw();
    if(panel.isCreateUsed()){
        NodesBox.Draw();
        EdgesBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->LoadFile.drawRectangleRounded(100);
        this->Apply.drawRectangleRounded(100);
        this->Random.drawText(BLACK);
        this->LoadFile.drawText(BLACK);
        this->Apply.drawText(BLACK);
    }
    else if(!panel.isUpdateUsed()){
        StartNodesBox.Draw();
    }
}

void ShortestPathState::resetBox(){
    NodesBox.resetBox();
    EdgesBox.resetBox();
    StartNodesBox.resetBox();
}

std::string ShortestPathState::getRandomInput(int nodes){
    srand(time(NULL));
    std::string input = "";
    int numNodes = rand()%nodes;
    input+=std::to_string(numNodes);
    return input;
}