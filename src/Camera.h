#pragma once

#include "ray.h"

class Camera {
public:
  Vec3 origin;
  Vec3 bottomLeftCorner;
  Vec3 vertical;
  Vec3 horizontal;
  Vec3 u, v, w;
  float lensRadius;

  // NOTE: verticalFOV is in degrees
  Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp, float verticalFOV, float aspect, float aperture, float focusDist) {
    lensRadius = aperture / 2.0;
    float fovRads = verticalFOV * PI / 180.0;
    float halfHeight = tan(fovRads / 2.0);
    float halfWidth = aspect * halfHeight;
    origin = lookFrom;

    w = normalize(lookFrom - lookAt);
    u = normalize(cross(viewUp, w));
    v = cross(w, u);

    bottomLeftCorner = origin - (halfWidth * focusDist * u) - (halfHeight * focusDist * v) - (focusDist * w);
    horizontal = 2.0 * halfWidth * focusDist * u;
    vertical = 2.0 * halfHeight * focusDist * v;
  }

  Ray getRay(float s, float t) {
    Vec3 lensOffset = lensRadius * randomPointInUnitDisk();
    Vec3 rayOrigin = origin + (u * lensOffset.x()) + (v * lensOffset.y());
    return Ray(rayOrigin, bottomLeftCorner + (s * horizontal) + (t * vertical) - rayOrigin);
  }

};