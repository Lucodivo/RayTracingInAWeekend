#pragma once

#include "Ray.h"

struct HitRecord {
  float t;
  Vec3 position;
  Vec3 normal;
};

class Hittable {
public:
  virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};

class HittableList: public Hittable {
public:
  Hittable **list;
  int size;

  HittableList() {};
  HittableList(Hittable **l, int count) : list(l), size(count) {};
  virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& returnRecord) const;
};

bool HittableList::hit(const Ray& ray, float tMin, float tMax, HitRecord& returnRecord) const
{
  HitRecord record;
  bool anyHit = false;
  double closestHit = tMax;
  for(int i = 0; i < size; i++) {
    if(list[i]->hit(ray, tMin, closestHit, record)) {
      anyHit = true;
      closestHit = record.t;
      returnRecord = record;
    }
  }
  return anyHit;
}
