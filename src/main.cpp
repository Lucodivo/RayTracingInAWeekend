#include <iostream>
#include <random>

#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Util.h"
#include "Camera.h"

#define MAX_FLOAT std::numeric_limits<float>::max()

const int pixelWidth = 200;
const int pixelHeight = 100;
const int antiAliasRayCount = 100;

std::default_random_engine randomGenerator;
std::uniform_real_distribution<float> randomFractionDistribution(0.0f, 1.0f);

Vec3 missColor(const Ray& r) {
  Vec3 normalizedDir = normalize(r.dir());
  float t = 0.5*(normalizedDir.y() + 1.0);
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

inline float randFraction() {
  return randomFractionDistribution(randomGenerator);
}

Vec3 randPointInUnitSphere() {
  Vec3 randomPoint;
  do{
    randomPoint = (Vec3(randFraction(), randFraction(), randFraction()) * 2.0) - Vec3(1.0, 1.0, 1.0);
  } while(randomPoint.lengthSquared() >= 1.0);
  return randomPoint;
}

Vec3 color(const Ray& ray, const Hittable* world) {
  HitRecord hitRec;
  if(world->hit(ray, 0.001, MAX_FLOAT, hitRec)) {
    Vec3 target = hitRec.position + hitRec.normal + randPointInUnitSphere();
    return color(Ray(hitRec.position, target - hitRec.position), world) * 0.5;
  }
  return missColor(ray);
}

int main()
{
  // ppm header: P3 means colors are in ascii, dimens are pixelWidth by pixelHeight, each pixel ranges from 0-255
  std::cout << "P3\n" << pixelWidth << " " << pixelHeight << "\n255\n";

  Hittable *spheres[2];
  spheres[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5);
  spheres[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100);
  Hittable *world = new HittableList(spheres, ArrayCount(spheres));
  Camera camera;
  for(int pixelY = pixelHeight - 1; pixelY > -1; --pixelY) {
    for(int pixelX = 0; pixelX < pixelWidth; ++pixelX ) {
      Vec3 col(0.0, 0.0, 0.0);
      for(int k = 0; k < antiAliasRayCount; ++k) {
        float u = float(pixelX + randFraction()) / float(pixelWidth);
        float v = float(pixelY + randFraction()) / float(pixelHeight);
        col += color(camera.getRay(u, v), world);
      }

      col /= float(antiAliasRayCount);
      col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int pixelRed = int(255.99 * col.r());
      int pixelGreen = int(255.99 * col.g());
      int pixelBlue = int(255.99 * col.b());

      std::cout << pixelRed << " " << pixelGreen << " " << pixelBlue << "\n";
    }
  }
}

