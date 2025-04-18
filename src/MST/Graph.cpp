#include "MST/Graph.h"
#include "MST/GraphEdge.h"
#include <raylib.h>
#include <set>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random> // Thêm để dùng std::shuffle

Graph::Graph() : vertices(0), edges(0) {}

Graph::Graph(std::vector<GraphNode*> vertices, std::vector<GraphEdge*> edges)
    : vertices(vertices), edges(edges) {
}

Graph::~Graph() {
    for (GraphNode* node : vertices) {
        delete node;
    }
    for (GraphEdge* edge : edges) {
        delete edge;
    }
}

void Graph::createGraph(int numOfVer) {
    if (numOfVer <= 0) {
        std::cout << "Lỗi: Số lượng đỉnh phải lớn hơn 0\n";
        return;
    }

    if (!vertices.empty() || !edges.empty()) {
        for (GraphNode* node : vertices) {
            delete node;
        }
        for (GraphEdge* edge : edges) {
            delete edge;
        }
        vertices.clear();
        edges.clear();
    }

    // --- Tạo các nút theo vòng tròn ---
    float radius = 300.0f;
    Vector2 center = {800.0f, 450.0f};
    float angleStep = 2 * PI / numOfVer;

    for (int i = 0; i < numOfVer; ++i) {
        float angle = i * angleStep;
        Vector2 pos = {
            center.x + radius * cosf(angle),
            center.y + radius * sinf(angle)
        };

        GraphNode* node = new GraphNode(i, {}, pos);
        node->size = 30.0f;
        node->colorNormal = BLACK;
        node->colorCurrent = BLACK;
        node->colorChosen = YELLOW;
        vertices.push_back(node);
    }

    // --- Tạo danh sách các cặp cạnh có thể (i, j) không trùng ---
    std::vector<std::pair<int, int>> possibleEdges;
    for (int i = 0; i < numOfVer; ++i) {
        for (int j = i + 1; j < numOfVer; ++j) {
            possibleEdges.emplace_back(i, j);
        }
    }

    // --- Tạo số lượng cạnh ngẫu nhiên ---
    int maxEdges = numOfVer * (numOfVer - 1) / 2;
    int minEdges = (numOfVer > 1) ? numOfVer - 1 : 0;
    int numEdges = 0;

    if (numOfVer > 1) {
        numEdges = rand() % (maxEdges - minEdges + 1) + minEdges;

        // Thay std::random_shuffle bằng std::shuffle
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(possibleEdges.begin(), possibleEdges.end(), g);

        for (int i = 0; i < numEdges; ++i) {
            int u = possibleEdges[i].first;
            int v = possibleEdges[i].second;
            int weight = rand() % 50 + 1;

            // Truyền con trỏ đến node thay vì tọa độ
            GraphEdge* edge = new GraphEdge(
                std::vector<GraphNode*>{vertices[u], vertices[v]},
                weight
            );

            edge->colorNormal = DARKGRAY;
            edge->colorChosen = YELLOW;
            edge->colorFlur = SKYBLUE;
            edge->currentColor = edge->colorNormal;
            edge->thick = 3.0f;

            vertices[u]->edge.push_back(edge);
            vertices[v]->edge.push_back(edge);
            edges.push_back(edge);
        }
    }

    std::cout << "Da tao " << vertices.size() << " nut va " << edges.size() << " canh.\n";
}

void Graph::DrawGraph() {
    if (vertices.empty()) return;
    for (GraphEdge* edge : edges) {
        if (edge) edge->DrawEdge();
    }
    for (GraphNode* node : vertices) {
        if (node) node->DrawNode();
    }
}

void Graph::Draw() {
    DrawGraph();
}

void Graph::Update() {
    for (GraphNode* node : vertices) {
        if (node) node->UpdatePosition();
    }
}