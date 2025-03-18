#ifndef SLLARROW_H
#define SLLARROW_H

#include "GUI/Arrow.h"
class SLLArrow : public Arrow{
    public:
        SLLArrow(Vector2 pos);
        void setLabel(const std::string &text);
        void setNull();
        bool checkNull();
        void setTarget(Vector2 targetPos) override;
        void draw() override;
    private:
        std::string label="";         
        bool isNull=false;  
};

#endif