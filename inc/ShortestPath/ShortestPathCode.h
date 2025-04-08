#ifndef SHORTESTPATHCODE_H
#define SHORTESTPATHCODE_H

#include <string>

const std::string DijkstraCode = {
    "Node cur = graph[startNode]\n"
    "cur.cost = 0\n"
    "while (cur != null)\n"
    "   for (Node neighbor : cur.neighbors)\n"
    "       if (cur.cost + edgeWeight < neighbor.cost)\n"
    "           neighbor.cost = cur.cost + edgeWeight\n"
    "   cur.visited = true\n"
    "   cur = getMinCostNode()\n"
};

#endif