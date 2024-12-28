#include "vec3.h"

#include <cmath>
#include <iostream>

vec3::vec3() {
  vec[0] = 0;
  vec[1] = 0;
  vec[2] = 0; 
}

vec3::vec3(float x,float y, float z) {
  vec[0] = x;
  vec[1] = y;
  vec[2] = z;
}

vec3::vec3(const vec3& v) {
  vec[0] = v.vec[0];
  vec[1] = v.vec[1];
  vec[2] = v.vec[2];
}

float vec3::x() const{
  return vec[0];
}

float vec3::y() const{
  return vec[1];
}

float vec3::z() const{
  return vec[2];
}

vec3 vec3::operator-() const {
  return vec3(-(this->vec[0]),
              -(this->vec[1]),
              -(this->vec[2]));
}

float vec3::operator[](int i) const {
  return vec[i];
}

float& vec3::operator[](int i) {
  return vec[i];
}

vec3& vec3::operator+=(const vec3& v) {
  vec[0] += v.vec[0];
  vec[1] += v.vec[1];
  vec[2] += v.vec[2];
  return *this; 
}

vec3& vec3::operator*=(const vec3& v){
  vec[0] *= v.vec[0];
  vec[1] *= v.vec[1];
  vec[2] *= v.vec[2];
  return *this;
}

vec3& vec3::operator/=(const vec3& v) {
  vec[0] /= v.vec[0];
  vec[1] /= v.vec[1];
  vec[2] /= v.vec[2];
  return *this;
}

static
float squared(float i) {
  return i * i;
}

float vec3::length() const {
  return sqrt(length_sqaured());
}

float vec3::length_sqaured() const{
  float x_sq = squared(vec[0]);
  float y_sq = squared(vec[1]);
  float z_sq = squared(vec[2]);
  return x_sq + y_sq + z_sq;
}

std::ostream& operator<<(std::ostream& out, const vec3& v){
  out << "("
      << v.x() << ", " 
      << v.y() << ", "
      << v.z() << ")";
   return out;
}

vec3 operator+(const vec3& v1,const vec3& v2){
  return vec3(v1[0] + v2[0],
              v1[1] + v2[1],
              v1[2] + v2[2]);
}

vec3 operator-(const vec3& v1,const vec3& v2){
  return vec3(v1[0] - v2[0],
              v1[1] - v2[1],
              v1[2] - v2[2]);
}

vec3 operator*(float t,const vec3& v){
  return vec3(t * v[0],
              t * v[1],
              t * v[2]);
}

vec3 operator*(const vec3& v, float t){
  return t * v;
}

vec3 operator/(const vec3& v, float t) {
  return (1/t) * v;
}

float dot(const vec3& v1, const vec3& v2){
  return v1.x() * v2.x() +
         v1.y() * v2.y() +
         v1.z() * v2.z();
}

vec3 unit_vec(const vec3& v){
  return v /( v.length() ) ;
}
