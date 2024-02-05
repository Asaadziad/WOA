#ifndef VEC3_H
#define VEC3_H


typedef struct vec3_t* Vec3;

Vec3 initVec3(int x, int y, int z);

int getX(Vec3 v);
int getY(Vec3 v);
int getZ(Vec3 v);

void setX(Vec3 v, int new_x);
void setY(Vec3 v, int new_y);
void setZ(Vec3 v, int new_z);

// Copies contents of v2 to v1
void copyVec(Vec3 v1, Vec3 v2);

#endif
