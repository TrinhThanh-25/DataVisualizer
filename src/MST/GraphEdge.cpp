#include "MST/GraphEdge.h"

GraphEdge::GraphEdge(std::vector<GraphNode*> nodes, int weight)
    : nodes(nodes), weight(weight) {
    colorNormal = lineColor;
    colorChosen = nodeHighlightColor;
    colorFlur = Fade(lineColor, 0.5f);
    currentColor = colorNormal;
    thick = 3.0f;
}

void GraphEdge::DrawEdge() {    
    if (nodes.size() != 2) return;
    DrawLineEx(nodes[0]->position, nodes[1]->position, thick, currentColor);
    Vector2 mid = {(nodes[0]->position.x + nodes[1]->position.x) / 2, 
                   (nodes[0]->position.y + nodes[1]->position.y) / 2};
    DrawText(std::to_string(weight).c_str(), mid.x, mid.y, 20, BLACK);
}