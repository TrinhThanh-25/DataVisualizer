#ifndef SLLARROW_H
#define SLLARROW_H

#include "raylib.h"
#include <string>
#include <cmath>

class SLLArrow{
     public:
          SLLArrow(Vector2 pos);
          
          void setLabel(const std::string &text);
          void setNull();
          void setTarget(Vector2 targetPos);
          void setPosition(Vector2 position);

          Vector2 getPosition();

          void drawArrow(Vector2 position, Vector2 destination);
          void update();
          void draw();
     private:
          Vector2 position;          
          Vector2 destination;       
          Vector2 targetDestination; 
          std::string label="";         
          bool isNull;  
};

#endif 