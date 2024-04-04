#include "vector2.h"

Vector2::Vector2() {}

Vector2::Vector2(float x, float y)
{
    this->x = x; this->y = y;
}

float Vector2::manhattan(Vector2* a, Vector2* b)
{
    if(a->x > b->x){
        if(a->y > b->y){
            return (a->x-b->x)+(a->y-b->y);
        }else{
            return (a->x-b->x)+(b->y-a->y);
        }
    }else{
        if(a->y > b->y){
            return (b->x-a->x)+(a->y-b->y);
        }else{
            return (b->x-a->x)+(b->y-a->y);
        }
    }
}
