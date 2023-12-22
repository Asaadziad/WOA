#ifndef VEC3_H
#define VEC3_H

class vec3 {
  public:
  vec3();
  vec3(float x,float y, float z);
  vec3(const vec3& v);

  // Methods
  float x() const;
  float y() const;
  float z() const;
  
  vec3 operator-() const;
  float operator[](int i) const;
  float& operator[](int i);
  vec3& operator+=(const vec3& v);
  vec3& operator*=(const vec3& v);
  vec3& operator/=(const vec3& v);  

  float length() const;
  float length_sqaured() const;
  private:
  float vec[3];
};

#endif
