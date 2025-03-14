#include "ShortestPath/ShortestPathNode.h"

ShortestPathNode::ShortestPathNode() {
    id = 0;
    cost = 0;
    isKnown = false;
    visited = false;
}

ShortestPathNode::ShortestPathNode(int id) {
    this->id = id;
    cost = 0;
    isKnown = false;
    visited = false;
}

ShortestPathNode::~ShortestPathNode() {
    for(auto node : adj){
        delete node;
    }
    adj.clear();
}

void ShortestPathNode::addAdj(ShortestPathNode* node) {
    adj.push_back(node);
}

std::vector<ShortestPathNode*> ShortestPathNode::getAdj() {
    return adj;
}

void ShortestPathNode::setID(int id) {
    this->id = id;
}

int ShortestPathNode::getID() {
    return id;
}

void ShortestPathNode::setCost(int cost) {
    this->cost = cost;
}

int ShortestPathNode::getCost() {
    return cost;
}

void ShortestPathNode::setVisited() {
    this->visited = true;
}

void ShortestPathNode::deVisited() {
    this->visited = false;
}

bool ShortestPathNode::getVisited() {
    return visited;
}

void ShortestPathNode::setKnown() {
    this->isKnown = true;
}

void ShortestPathNode::deKnown() {
    this->isKnown = false;
}

bool ShortestPathNode::getKnown() {
    return isKnown;
}

Vector2 ShortestPathNode::getPosition() {
    return position;
}

void ShortestPathNode::setPosition(Vector2 position) {
    this->position = position;
    node = {position.x-STNodeSize.x/2.0f,position.y-STNodeSize.y/2.0f, STNodeSize.x, STNodeSize.y};
    for(auto a : arrow){
        a->setPosition(position);
    }
}

void ShortestPathNode::addEdge(ShortestPathNode* node) {
    STArrow* a = new STArrow(position);
    a->setFrom(id);
    a->setTo(node->getID());
    a->setTarget(node->getPosition());
    arrow.push_back(a);
}

void ShortestPathNode::removeEdge(ShortestPathNode* node) {
    for(auto a : arrow){
        if(a->getTo() == node->getID()){
            arrow.erase(std::remove(arrow.begin(), arrow.end(), a), arrow.end());
            delete a;
            break;
        }
    }
}

void ShortestPathNode::clearEdges() {
    for(auto a : arrow){
        delete a;
    }
    arrow.clear();
}

void ShortestPathNode::update() {
    for(auto arrow : arrow){
        arrow->setTarget(adj[arrow->getTo()]->getPosition());
        arrow->update();
    }
}

void ShortestPathNode::draw(bool isWeighted, bool isDirected) {
    for(auto arrow : arrow){
        arrow->draw(isWeighted, isDirected);
    }
    DrawRectangleRounded(node, 100, 0, visited ? RED : LIGHTGRAY);
    DrawText(std::to_string(cost).c_str(), position.x+STNodeSize.x/2.0f, position.y-STNodeSize.y/2.0f, 12, BLACK);
    DrawText(std::to_string(id).c_str(), position.x-MeasureText(std::to_string(id).c_str(),24)/2.0f,position.y-12,24,BLACK);
}

