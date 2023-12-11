#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} Vector2f;

Vector2f addVectors(Vector2f v1, Vector2f v2);
Vector2f subVectors(Vector2f v1, Vector2f v2);
Vector2f scalarMulVector(Vector2f v,int scalar);

float getMagnitude(Vector2f v);

#endif