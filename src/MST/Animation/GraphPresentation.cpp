#include "MST/Animation/GraphPresentation.h"

GraphPresentation::GraphPresentation(float & speed, Graph * graph): speed(speed), graph(graph), currentStep(0) {
    parent.resize(3, 0);
    rank.resize(3, 0);
}

void GraphPresentation::CreateGraph(int numofNode){
    graph->createGraph(numofNode);

    //move to finpos
    GraphSetofOperation movetoFin(speed);
    for(int i = 0; i < graph->vertices.size(); i++){
        //std::cout<<"toi day"<<std::endl;
        GraphOperation move(speed, graph->vertices[i]);
        move.type = GraphOperation::MOVE_NODE;
        movetoFin.AddOperation(move);
    }
    this->SetOperations.push_back(movetoFin);
    return;
}

// Hàm Disjoint Set
void GraphPresentation::initDisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Mỗi node là tập hợp riêng
    }
}

int GraphPresentation::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

bool GraphPresentation::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return false; // Đã cùng tập hợp, tạo chu trình

    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}

void GraphPresentation::Kruskal() {
    if (graph == nullptr || graph->vertices.empty()) return;

    // Khởi tạo Disjoint Set
    int numVertices = graph->vertices.size();
    initDisjointSet(numVertices);

    // Sắp xếp các cạnh theo trọng số
    std::vector<GraphEdge*> sortedEdges = graph->edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), 
        [](GraphEdge* a, GraphEdge* b) { return a->weight < b->weight; });

    // Duyệt qua từng cạnh
    for (GraphEdge* edge : sortedEdges) {
        // Tìm node đầu và cuối của cạnh
        GraphNode* node1 = edge->nodes[0];
        GraphNode* node2 = edge->nodes[1];
        int u = node1->data;
        int v = node2->data;

        // Animation: Làm sáng cạnh đang xét
        GraphSetofOperation highlightEdge(speed);
        GraphOperation highlightEdgeOp(speed, edge);
        highlightEdgeOp.type = GraphOperation::FLUR_EDGE;
        highlightEdge.AddOperation(highlightEdgeOp);

        // Animation: Làm sáng hai node liên quan
        GraphOperation highlightNode1(speed, node1);
        highlightNode1.type = GraphOperation::CHOSEN_NODE;
        highlightEdge.AddOperation(highlightNode1);
        GraphOperation highlightNode2(speed, node2);
        highlightNode2.type = GraphOperation::CHOSEN_NODE;
        highlightEdge.AddOperation(highlightNode2);

        SetOperations.push_back(highlightEdge);

        // Kiểm tra chu trình
        if (unionSets(u, v)) {
            // Không tạo chu trình, thêm cạnh vào MST
            GraphSetofOperation addEdgeToMST(speed);
            GraphOperation addEdgeOp(speed, edge);
            addEdgeOp.type = GraphOperation::CHOSEN_EDGE;
            addEdgeToMST.AddOperation(addEdgeOp);

            // Đổi màu node về bình thường
            GraphOperation resetNode1(speed, node1);
            resetNode1.type = GraphOperation::NORMAL_NODE;
            addEdgeToMST.AddOperation(resetNode1);
            GraphOperation resetNode2(speed, node2);
            resetNode2.type = GraphOperation::NORMAL_NODE;
            addEdgeToMST.AddOperation(resetNode2);

            SetOperations.push_back(addEdgeToMST);
        } else {
            // Tạo chu trình, bỏ qua cạnh này
            GraphSetofOperation rejectEdge(speed);
            GraphOperation rejectEdgeOp(speed, edge);
            rejectEdgeOp.type = GraphOperation::NORMAL_EDGE;
            rejectEdge.AddOperation(rejectEdgeOp);

            // Đổi màu node về bình thường
            GraphOperation resetNode1(speed, node1);
            resetNode1.type = GraphOperation::NORMAL_NODE;
            rejectEdge.AddOperation(resetNode1);
            GraphOperation resetNode2(speed, node2);
            resetNode2.type = GraphOperation::NORMAL_NODE;
            rejectEdge.AddOperation(resetNode2);

            SetOperations.push_back(rejectEdge);
        }
    }
    GraphSetofOperation highlightAll(speed);
    for(int i = 0; i < graph->vertices.size(); i++){
        GraphOperation hl(speed, graph->vertices[i]);
        highlightAll.AddOperation(hl);
    }
    SetOperations.push_back(highlightAll);

    std::cout << "Kruskal completed with " << SetOperations.size() << " animation steps.\n";
}

bool GraphPresentation::DrawPresentation(){
    if(SetOperations.empty() || currentStep >= SetOperations.size()){
        if(SetOperations.empty()){
            std::cout<<"empty mat roi.\n";
        }
        return true;
    }

    if(SetOperations[currentStep].Draw()){
        std::cout<<"CO ANIMATION NGHEN.\n";
        currentStep++;
    }
    if(currentStep >= SetOperations.size()){
        currentStep = 0;
        this->SetOperations.clear();
        return true;
    }
    return false;
}