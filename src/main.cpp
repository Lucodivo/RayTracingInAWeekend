#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Util.h"

#define MAX_FLOAT std::numeric_limits<float>::max()

const int pixelWidth = 200;
const int pixelHeight = 100;
const Vec3 eyeOrigin = Vec3(0.0, 0.0, 0.0);
const Vec3 bottomLeftCorner = Vec3(-2.0, -1.0, -1.0);
const float width = 4.0;
const float height = 2.0;

const Vec3 sphereColor = Vec3(1.0, 0.0, 0.0);

Vec3 missColor(const Ray& r) {
  Vec3 normalizedDir = normalize(r.dir());
  float t = 0.5*(normalizedDir.y() + 1.0);
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

Vec3 color(const Ray& ray, const Hittable* world) {
  HitRecord hitRec;
  if(world->hit(ray, 0.0, MAX_FLOAT, hitRec)) {
    return (hitRec.normal + 1.0) * 0.5;
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
  for(int pixelY = pixelHeight - 1; pixelY > -1; --pixelY) {
    for(int pixelX = 0; pixelX < pixelWidth; ++pixelX ) {
      float u = float(pixelX) / float(pixelWidth);
      float v = float(pixelY) / float(pixelHeight);

      Ray ray(eyeOrigin, bottomLeftCorner + Vec3(u * width, v * height, 0.0));

      Vec3 col = color(ray, world);
      int pixelRed = int(255.99 * col.r());
      int pixelGreen = int(255.99 * col.g());
      int pixelBlue = int(255.99 * col.b());

      std::cout << pixelRed << " " << pixelGreen << " " << pixelBlue << "\n";
    }
  }

  return 0;
}
