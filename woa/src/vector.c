#include "../headers/vector.h"
#include "math.h"

Vector2f addVectors(Vector2f v1, Vector2f v2){
    Vector2f tmp;
    tmp.x = v1.x + v2.x;
    tmp.y = v2.y + v2.y;
    return tmp;
}

Vector2f subVectors(Vector2f v1, Vector2f v2){
    Vector2f tmp;
    tmp.x = v1.x - v2.x;
    tmp.y = v1.y - v2.y;
    return tmp;
}

Vector2f scalarMulVector(Vector2f v,int scalar){
    Vector2f tmp;
    tmp.x = scalar * v.x;
    tmp.y = scalar * v.y;
    return tmp;
}

float getMagnitude(Vector2f v){
    return sqrtf(v.x*v.x + v.y*v.y);
}