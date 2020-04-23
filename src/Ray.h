//
// Created by Connor on 4/21/2020.
//
#pragma once

#include "Vec3.h"

class Ray
{
public:
  Vec3 o;
  Vec3 d;

  Ray() {}
  Ray(const Vec3& origin, const Vec3& dir) { o = origin; d = dir; }
  Vec3 origin() const { return o; }
  Vec3 dir() const { return d; }
  Vec3 at(float t) const { return o + t * d; }
};