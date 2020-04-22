//
// Created by Connor on 4/21/2020.
//
#pragma once

#include "vec3.h"

class ray
{
public:
  vec3 o;
  vec3 d;

  ray() {}
  ray(const vec3& origin, const vec3& dir) { o = origin; d = dir; }
  vec3 origin() const { return o; }
  vec3 dir() const { return d; }
  vec3 at(float t) const { return o + t * d; }
};