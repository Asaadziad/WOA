#include "../../headers/vec3.h"
#include "stdlib.h"


struct vec3_t {
  int x;
  int y;
  int z;
};

Vec3 initVec3(int x, int y, int z){
  Vec3 new_v = (Vec3)malloc(sizeof(*new_v));
  if(!new_v) return NULL;
  new_v->x = x;
  new_v->y = y;
  new_v->z = z;
  return new_v;
}

int getX(Vec3 v){ return v->x;}
int getY(Vec3 v){ return v->y;}
int getZ(Vec3 v){ return v->z;}

void setX(Vec3 v, int new_x){ v->x = new_x;}
void setY(Vec3 v, int new_y){ v->y = new_y;}
void setZ(Vec3 v, int new_z){ v->z = new_z;}

void copyVec(Vec3 v1, Vec3 v2) {
  setX(v1, getX(v2));
  setY(v1, getY(v2));
  setZ(v1, getZ(v2));

}

