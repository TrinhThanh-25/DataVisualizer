#ifndef ARROW_H
#define ARROW_H

#include "raylib.h"
#include <string>
#include <cmath>

class Arrow{
     public:
          Arrow(Vector2 pos);
          
          virtual void setTarget(Vector2 targetPos);
          void setPosition(Vector2 position);
          Vector2 getPosition();

          virtual void drawArrow(Vector2 position, Vector2 destination);
          virtual void update();
          virtual void draw();
     protected:
          Vector2 position;          
          Vector2 destination;       
          Vector2 targetDestination; 
     private:
          
          
};

#endif 