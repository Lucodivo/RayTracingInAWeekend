#pragma once

#include "Vec3.h"
#include "Hittable.h"

class Sphere: public Hittable {
public:
  Vec3 center;
  float radius;

  Sphere() {}
  Sphere(Vec3 c, float r) : center(c), radius(r) {};
  virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;
};

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
  Vec3 centerToOrigin = r.origin() - center;
  float a = dot(r.dir(), r.dir());
  float b = dot(centerToOrigin, r.dir());
  float c = dot(centerToOrigin, centerToOrigin) - radius * radius;
  float discriminant = b*b - a*c;

  if (discriminant <= 0) return false;

  float sqrtDisc = sqrt(discriminant);

  float value = (-b - sqrtDisc) / a;
  if(value < tMax && value > tMin) {
    rec.t = value;
    rec.position = r.at(value);
    rec.normal = (rec.position - center) / radius;
    return true;
  }

  value = (-b + sqrtDisc) / a;
  if(value < tMax && value > tMin) {
    rec.t = value;
    rec.position = r.at(value);
    rec.normal = (rec.position - center) / radius;
    return true;
  }

  return false;
}