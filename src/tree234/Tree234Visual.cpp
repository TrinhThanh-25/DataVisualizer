#include <234tree/Tree234Visual.h>
#include <string>

Tree234Visual::Tree234Visual(float & speed) :speed(speed), root(nullptr), currentPresentationIndex(-1), currentStateIndex(0), historyState({}), inputPanel({30, 700}, {150, 200}), speedSlider(0.01f, 0.1f, 0.05f, 10), 
                                  playbackControl({900, 600}, 200, 10, speed) ,treePresentation(speed, root, historyState, currentPresentationIndex, currentStateIndex) {    
    //root = nullptr;
    //speed = 0.05f;
    //std::vector<std::vector<TreeNode*>> history;
    //int presIndex = 0, stateIndex = 0;
    
    showInputBox = false;
    inputText = "";
    inputNumber = 0;
    insertButton = {20, 20, 100, 40};
    isRewinding = false;
    
    currentPresentationIndex = -1;
    currentStateIndex = 0;
    //inputPanel = InputPanel({150, 500}, {150, 200}, LIGHTGRAY);
}

Tree234Visual::~Tree234Visual() {
    //delete treePresentation;
    // TODO: Thêm logic để delete toàn bộ cây (root)
}

void Tree234Visual::Update() {
    inputPanel.Update();

    if(inputPanel.IsLoadFilePressed()){
        auto fileValues = inputPanel.GetFileValues2D();
        int activeButton = inputPanel.GetActiveButtonIndex();

        if(!fileValues.empty()){
            switch (activeButton)
            {
            case 0:{
                if(fileValues.size() >= 2 && !fileValues[0].empty()){
                    int size = fileValues[0][0];
                    std::vector<int> keys = fileValues[1];
                    root->CreateTreewithKey(keys);
                    root->calculateCoordinate({800, 100});
                    treePresentation.clear();
                    treePresentation.CreateTree(size);
                }
                break;
            }
            case 1:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    treePresentation.clear();
                    treePresentation.FindKeyOperation(key);
                }
                break;
            }
            case 2:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    std::cout<<"INSERT: "<<key<<std::endl;
                    treePresentation.clear();
                    treePresentation.InsertKeyOperation(key);
                    break;
                }
            }
            case 3:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    treePresentation.clear();
                    treePresentation.DeleteKeyOperation(key);
                }
                break;
            }
            }
            inputPanel.ResetInputState();
        }
    }
    else{
        // Lấy giá trị từ InputPanel và hành động đã chọn
        int inputValue = inputPanel.GetInputText();
        int activeButton = inputPanel.GetActiveButtonIndex();

        // Chỉ thực hiện hành động nếu vừa nhấn "Go" và có giá trị hợp lệ
        if (inputValue != -1 && activeButton != -1) {
            switch (activeButton) {
                case 0: // Create
                    // Tạo cây mới (đã comment trong code gốc, tôi giữ nguyên)
                    /*
                    root = new TreeNode({}, {}, {400, 100});
                    treePresentation->tree = root;
                    treePresentation->current = root;
                    treePresentation->isFinished = false;
                    treePresentation->clear();
                    */
                    this->root = this->root->CreateTree(inputValue);
                    this->root->calculateCoordinate({800, 100});
                    std::cout<<"da tao tree roi"<<std::endl;
            
                    treePresentation.clear();
                    treePresentation.CreateTree(inputValue);
                    std::cout << "Create button pressed\n";
                    break;
                case 1: // Search
                    treePresentation.clear();
                    inputNumber = inputValue;
                    treePresentation.FindKeyOperation(inputNumber);
                    std::cout << "Search key: " << inputNumber << std::endl;
                    break;
                case 2: // Insert
                    treePresentation.clear();
                    Insert(inputValue);
                    std::cout << "Insert key: " << inputValue << std::endl;
                    break;
                case 3: // Remove
                    treePresentation.clear();
                    inputNumber = inputValue;
                    treePresentation.DeleteKeyOperation(inputNumber);
                    std::cout << "Remove key: " << inputNumber << std::endl;
                    break;
            }
            // Reset trạng thái của InputPanel sau khi thực hiện hành động
            inputPanel.ResetInputState();
        }
    }

    


    speedSlider.Update();
    if(isPlaying == true){
        if(playbackControl.isSkip == true){
            this->isDrawTree = false;
            speed = 1.0f;
        }
        else{
            speed = speedSlider.val;
        }
    }
    else{
        speed = speedSlider.val;
    }
    

    playbackControl.UpdateTree234(currentPresentationIndex, currentStateIndex, historyState);

    if(playbackControl.isPlaying){
        this->isRewinding = true;
    }
    else{
        this->isRewinding = false;
    }

}

void Tree234Visual::Draw() {
    inputPanel.Draw();
    //std::cout<<"Drawing tree with keys: "<<std::endl;
    
    if(treePresentation.DrawPresentation()){
        speed = speedSlider.val;
        this->isPlaying = false;
        isDrawTree = true;
        playbackControl.isSkip = false;
    }
    else{
        this->isPlaying = true;
    }
    speedSlider.Draw();
    playbackControl.Draw();
    //root->calculateCoordinate({800, 100});

    //std::cout<<"isRewinding: "<<isRewinding<<std::endl;
    if(this->isRewinding == false){
        //std::cout<<"draw current"<<std::endl;
        if(isDrawTree){
            DrawTree(root);
        }
    }
    else{
        //std::cout<<"draw history"<<std::endl;
        DrawTree(historyState[currentPresentationIndex][currentStateIndex]);
    }
}

void Tree234Visual::DrawTree(TreeNode* root) {
    if(!root) return;

    //root->LayoutTree(0, 800, 0, 100); // Căn chỉnh vị trí của cây
    //std::cout<<"Drawing tree with keys: "<<std::endl;
    if (root) {
        
        root->DrawLinktoChild();
        root->DrawNode();
        for (TreeNode* child : root->children) {
            DrawTree(child);
        }
    }
}

void Tree234Visual::Insert(int key) {
    treePresentation.clear();
    treePresentation.InsertKeyOperation(key);
    //treePresentation->DrawPresentation();
}

void Tree234Visual::UpdateTheme(TreeNode * root){
    if(root == nullptr) return;

    root->colorNormal = nodeColor;
    root->colorChosen = nodeHighlightColor;
    root->currentColor = root->colorNormal;

    root->textChosenColor = nodeHighlightTextColor;
    root->textNorColor = nodeTextColor;
    root->textCurColor = root->textNorColor;

    for(int i = 0; i < root->children.size(); i++){
        TreeNode * child = root->children[i];
        UpdateTheme(child);
    }

}