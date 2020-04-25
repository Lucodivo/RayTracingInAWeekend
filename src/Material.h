#pragma once

#include "Ray.h"
#include "Hittable.h"
#include "Util.h"
#include "Vec3.h"

class Material {
public:
  virtual bool scatter(const Ray& rayIn, const HitRecord& hitRec, Vec3& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian : public Material {
public:
  Vec3 albedo;

  Lambertian(const Vec3& a) : albedo(a) {};
  bool scatter(const Ray& rayIn, const HitRecord& hitRec, Vec3& attenuation, Ray& scatteredRay) const {
    Vec3 target = hitRec.position + hitRec.normal + randPointInUnitSphere();
    scatteredRay = Ray(hitRec.position, target - hitRec.position);
    attenuation = albedo;
    return true;
  }
};

class Metal : public Material {
public:
  Vec3 albedo;
  float fuzz;

  Metal(const Vec3& a, float f) : albedo(a) { fuzz = f < 1.0 ? f : 1.0; };
  bool scatter(const Ray& rayIn, const HitRecord& hitRec, Vec3& attenuation, Ray& scatteredRay) const {
    Vec3 reflected = reflect(normalize(rayIn.dir()), hitRec.normal);
    scatteredRay = Ray(hitRec.position, reflected + fuzz * randPointInUnitSphere());
    attenuation = albedo;
    // only scatter ray if the reflected ray points out of the surface
    return dot(reflected, hitRec.normal) > 0.0;
  }
};