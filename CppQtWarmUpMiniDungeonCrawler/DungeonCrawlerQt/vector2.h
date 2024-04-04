#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2();
    Vector2(float x,float y);

    float x;float y;
    ///kind of distance
    static float manhattan(Vector2* a, Vector2* b);
};

#endif // VECTOR2_H
