#pragma once

#include "ray.h"

class Camera {
public:
  Vec3 origin;
  Vec3 bottomLeftCorner;
  Vec3 vertical;
  Vec3 horizontal;

  // NOTE: verticalFOV is in degrees
  Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp, float verticalFOV, float aspect) {
    float fovRads = verticalFOV * PI / 180.0;
    float halfHeight = tan(fovRads / 2.0);
    float halfWidth = aspect * halfHeight;
    origin = lookFrom;

    Vec3 w = normalize(lookFrom - lookAt);
    Vec3 u = normalize(cross(viewUp, w));
    Vec3 v = normalize(cross(w, u));

    bottomLeftCorner = origin - (halfWidth * u) - (halfHeight * v) - w;
    horizontal = 2.0 * halfWidth * u;
    vertical = 2.0 * halfHeight * v;
  }

  Ray getRay(float u, float v) {
    return Ray(origin, bottomLeftCorner + (u * horizontal) + (v * vertical) - origin);
  }

};