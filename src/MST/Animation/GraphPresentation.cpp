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
        hl.type = GraphOperation::CHOSEN_NODE;
        highlightAll.AddOperation(hl);
    }
    SetOperations.push_back(highlightAll);

    std::cout << "Kruskal completed with " << SetOperations.size() << " animation steps.\n";
}

// void GraphPresentation::Prim() {
//     if (graph == nullptr || graph->vertices.empty()) return;

//     int numVertices = graph->vertices.size();
//     std::vector<bool> inMST(numVertices, false); // Đánh dấu node đã thuộc MST
//     std::vector<int> key(numVertices, INT_MAX); // Trọng số nhỏ nhất để đến node
//     std::vector<GraphEdge*> mstEdge(numVertices, nullptr); // Lưu cạnh thuộc MST

//     // Hàng đợi ưu tiên để chọn cạnh có trọng số nhỏ nhất
//     std::priority_queue<GraphEdge*> pq;

//     // Bắt đầu từ node 0
//     int startVertex = 0;
//     key[startVertex] = 0;

//     // Highlight node bắt đầu
//     GraphSetofOperation startStep(speed);
//     GraphOperation highlightStartNode(speed, graph->vertices[startVertex]);
//     highlightStartNode.type = GraphOperation::CHOSEN_NODE;
//     startStep.AddOperation(highlightStartNode);
//     SetOperations.push_back(startStep);

//     // Thêm tất cả các cạnh từ node bắt đầu vào hàng đợi
//     inMST[startVertex] = true;
//     for (GraphEdge* edge : graph->vertices[startVertex]->edge) {
//         GraphNode* node1 = edge->nodes[0];
//         GraphNode* node2 = edge->nodes[1];
//         int otherVertex = (node1->data == startVertex) ? node2->data : node1->data;
//         if (!inMST[otherVertex]) {
//             key[otherVertex] = edge->weight;
//             mstEdge[otherVertex] = edge;
//             pq.push({edge->weight, edge, node1, node2});
//         }
//     }

//     // Lặp cho đến khi tất cả node được thêm vào MST
//     while (!pq.empty()) {
//         // Lấy cạnh có trọng số nhỏ nhất
//         GraphEdge *  minEdge = pq.top();
//         pq.pop();

//         GraphEdge* edge = minEdge.edge;
//         GraphNode* node1 = minEdge.node1;
//         GraphNode* node2 = minEdge.node2;

//         // Xác định node nào chưa thuộc MST
//         int u = node1->data;
//         int v = node2->data;
//         int newVertex = inMST[u] ? v : u;
//         if (inMST[newVertex]) continue; // Bỏ qua nếu cả hai node đã thuộc MST

//         // Highlight cạnh và hai node
//         GraphSetofOperation highlightStep(speed);
//         GraphOperation highlightEdgeOp(speed, edge);
//         highlightEdgeOp.type = GraphOperation::FLUR_EDGE;
//         highlightStep.AddOperation(highlightEdgeOp);

//         GraphOperation highlightNode1(speed, node1);
//         highlightNode1.type = GraphOperation::CHOSEN_NODE;
//         highlightStep.AddOperation(highlightNode1);

//         GraphOperation highlightNode2(speed, node2);
//         highlightNode2.type = GraphOperation::CHOSEN_NODE;
//         highlightStep.AddOperation(highlightNode2);

//         SetOperations.push_back(highlightStep);

//         // Thêm node mới vào MST
//         inMST[newVertex] = true;

//         // Thêm cạnh vào MST
//         GraphSetofOperation addEdgeStep(speed);
//         GraphOperation addEdgeOp(speed, edge);
//         addEdgeOp.type = GraphOperation::CHOSEN_EDGE;
//         addEdgeStep.AddOperation(addEdgeOp);

//         // Trả node về trạng thái bình thường
//         GraphOperation resetNode1(speed, node1);
//         resetNode1.type = GraphOperation::NORMAL_NODE;
//         addEdgeStep.AddOperation(resetNode1);

//         GraphOperation resetNode2(speed, node2);
//         resetNode2.type = GraphOperation::NORMAL_NODE;
//         addEdgeStep.AddOperation(resetNode2);

//         SetOperations.push_back(addEdgeStep);

//         // Thêm các cạnh mới từ node vừa thêm vào hàng đợi
//         for (GraphEdge* nextEdge : graph->vertices[newVertex]->edge) {
//             GraphNode* nextNode1 = nextEdge->nodes[0];
//             GraphNode* nextNode2 = nextEdge->nodes[1];
//             int otherVertex = (nextNode1->data == newVertex) ? nextNode2->data : nextNode1->data;
//             if (!inMST[otherVertex] && nextEdge->weight < key[otherVertex]) {
//                 key[otherVertex] = nextEdge->weight;
//                 mstEdge[otherVertex] = nextEdge;
//                 pq.push({nextEdge->weight, nextEdge, nextNode1, nextNode2});
//             }
//         }
//     }

//     std::cout << "Prim completed with " << SetOperations.size() << " animation steps.\n";
// }

bool GraphPresentation::DrawPresentation(){
    if(SetOperations.empty() || currentStep >= SetOperations.size()){
        // if(SetOperations.empty()){
        //     //std::cout<<"empty mat roi.\n";
        // }
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