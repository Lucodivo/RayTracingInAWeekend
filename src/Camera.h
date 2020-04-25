#pragma once

#include "ray.h"

class Camera {
public:
  Vec3 origin;
  Vec3 bottomLeftCorner;
  float width;
  float height;


  Camera() {
    origin = Vec3(0.0, 0.0, 0.0);
    bottomLeftCorner = Vec3(-2.0, -1.0, -1.0);
    width = 4.0;
    height = 2.0;
  }

  Ray getRay(float u, float v) {
    return Ray(origin, bottomLeftCorner + Vec3(u * width, v * height, 0.0) - origin);
  }

};