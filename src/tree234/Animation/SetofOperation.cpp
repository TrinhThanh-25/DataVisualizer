<<<<<<< HEAD
<<<<<<< HEAD
#include <234tree/animation/SetofOperation.h>

SetofOperation::SetofOperation(float & speed) : speed(speed) {}
=======
#include "SetofOperation.h"

SetofOperation::SetofOperation(Font fontNumber, Font fontText, float & speed) : fontNumber(fontNumber), fontText(fontText), speed(speed) {}
>>>>>>> 14909f1 (234tree animation)



=======
#include <234tree/animation/SetofOperation.h>

SetofOperation::SetofOperation(float & speed) : speed(speed) {}



>>>>>>> eef9140bc23233bdd1bb6c4cd04b98d73a4dbe43
void SetofOperation::AddOperation(Operation operation){
    operations.push_back(operation);
}

bool SetofOperation::Draw(){
    if(operations.empty()) return true;
    bool isComplete = true;
    for(int i = 0; i < operations.size(); i++){
        if(!operations[i].DrawOperation()){
            isComplete = false;
        }
    }
    return isComplete;
}