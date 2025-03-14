#include "ShortestPath/ShortestPath.h"

ShortestPath::ShortestPath() {
    isWeighted = false;
    isDirected = false;
}

ShortestPath::~ShortestPath() {
   clearGraph();
}

void ShortestPath::createGraph(int nodes, int edges){
    clearGraph();
    for(int i = 0; i < nodes; i++){
        ShortestPathNode* n = new ShortestPathNode();
        n->setID(i);
        graph.push_back(n);
    }
    for(int i = 0; i < edges; i++){
        int node1 = rand()%nodes;
        int node2 = rand()%nodes;
        addEdge(node1, node2);
    }
}

void ShortestPath::addEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->addEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->addEdge(graph[node1]);
        }
    }
}

void ShortestPath::removeEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->removeEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->removeEdge(graph[node1]);
        }
    }
}

void ShortestPath::searchPath(int startNode, int endNode){}

void ShortestPath::clearGraph(){
    for(auto n : graph){
        n->clearEdges();
        delete n;
    }
    graph.clear();
}

void ShortestPath::resetGraph(){
    for(auto n : graph){
        n->deVisited();
        n->deKnown();
    }
}

void ShortestPath::setWeighted(){
    isWeighted = true;
}

void ShortestPath::deWeighted(){
    isWeighted = false;
}

void ShortestPath::setDirected(){
    isDirected = true;
}

void ShortestPath::deDirected(){
    isDirected = false;
}

void ShortestPath::GridBasedPlacement(std::vector<ShortestPathNode*>& graph,int screenWidth, int screenHeight){
    int rows = sqrt(graph.size());
    int cols = graph.size()/rows;
    int x = 0;
    int y = 0;
    for(auto n : graph){
        n->setPosition({(float)x,(float)y});
        x += 100;
        if(x >= screenWidth){
            x = 0;
            y += 100;
        }
    }
}

void ShortestPath::Dijkstra(int startNode){}

void ShortestPath::update(){
    for(auto n : graph){
        n->update();
    }
}

void ShortestPath::draw(){
    for(auto n : graph){
        n->draw(isWeighted, isDirected);
    }
}