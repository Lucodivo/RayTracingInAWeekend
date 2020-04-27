#pragma once

#include "Ray.h"
#include "Hittable.h"
#include "Util.h"
#include "Vec3.h"

float schlickReflectProbability(float cosine, float refractiveIndex) {
  float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
  r0 = r0 * r0;
  return r0 + ((1 - r0) * pow((1 - cosine), 5));
}

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

class Dielectric : public Material {
public:
  float refractiveIndex;

  Dielectric(float ri) : refractiveIndex(ri) {}
  bool scatter(const Ray &rayIn, const HitRecord &hitRec, Vec3 &attenuation, Ray &scatteredRay) const {
    Vec3 normal;
    float iorIncomingOverOutgoing;
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;

    // If the cosine of the ray in and normal is positive (the angle is between (-Pi/2, Pi/2)),
    // the ray is coming from "inside" the surface and the surface normal needs to be reversed
    float projRayOnNorm = dot(rayIn.dir(), hitRec.normal);
    float cosine = projRayOnNorm / rayIn.dir().length();
    if(cosine > 0.0) { // inside surface
      normal = -hitRec.normal;
      iorIncomingOverOutgoing = refractiveIndex;
      // TODO: I don't understand this. How does the refractive index have anything to do with the incoming angle's cosine??
      cosine *= refractiveIndex;
    } else { // outside surface
      normal = hitRec.normal;
      iorIncomingOverOutgoing = 1.0 / refractiveIndex;
      // the ray
      cosine *= -1;
    }


    float reflectProbability = schlickReflectProbability(cosine, refractiveIndex);
    if(randFraction() >= reflectProbability && refract(rayIn.dir(), normal, iorIncomingOverOutgoing, refracted)) {
      scatteredRay = Ray(hitRec.position, refracted);
    } else {
      Vec3 reflected = reflect(rayIn.dir(), hitRec.normal);
      scatteredRay = Ray(hitRec.position, reflected);
    }

    return true;
  }
};