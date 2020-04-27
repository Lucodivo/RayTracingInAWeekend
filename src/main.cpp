#include <iostream>

#include "Vec3.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Util.h"
#include "Camera.h"
#include "Material.h"

#define MAX_FLOAT std::numeric_limits<float>::max()
#define MAX_ITERATIONS 50

const int pixelWidth = 200;
const int pixelHeight = 100;
const int antiAliasRayCount = 100;

Vec3 missColor(const Ray& r) {
  Vec3 normalizedDir = normalize(r.dir());
  float t = 0.5*(normalizedDir.y() + 1.0);
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

Vec3 color(const Ray& ray, const Hittable* world, int iteration) {
  HitRecord hitRec;
  if(world->hit(ray, 0.001, MAX_FLOAT, hitRec)) {
    Ray scattered;
    Vec3 attenuation;
    if(iteration < MAX_ITERATIONS && hitRec.materialPtr->scatter(ray, hitRec, attenuation, scattered)) {
      return attenuation * color(scattered, world, iteration + 1);
    } else {
      return Vec3(0.0, 0.0, 0.0);
    }
  }

  return missColor(ray);
}

int main()
{
  // ppm header: P3 means colors are in ascii, dimens are pixelWidth by pixelHeight, each pixel ranges from 0-255
  std::cout << "P3\n" << pixelWidth << " " << pixelHeight << "\n255\n";

  Hittable *spheres[] = {
          new Sphere(Vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5))),
          new Sphere(Vec3(0.0, -100.5, -1.0), 100, new Lambertian(Vec3(0.8, 0.8, 0.0))),
          new Sphere(Vec3(1.0, 0, -1.0), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.3)),
          new Sphere(Vec3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.5)),
          new Sphere(Vec3(-1.0, 0.0, -1.0), -0.45, new Dielectric(1.5))
  };
  Hittable *world = new HittableList(spheres, ArrayCount(spheres));
  Camera camera;
  for(int pixelY = pixelHeight - 1; pixelY >= 0; --pixelY) {
    for(int pixelX = 0; pixelX < pixelWidth; ++pixelX ) {
      Vec3 col(0.0, 0.0, 0.0);
      for(int k = 0; k < antiAliasRayCount; ++k) {
        float u = float(pixelX + randFraction()) / float(pixelWidth);
        float v = float(pixelY + randFraction()) / float(pixelHeight);
        col += color(camera.getRay(u, v), world, 0);
      }

      col /= float(antiAliasRayCount);
      col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int pixelRed = int(255.99 * col.r());
      int pixelGreen = int(255.99 * col.g());
      int pixelBlue = int(255.99 * col.b());

      std::cout << pixelRed << " " << pixelGreen << " " << pixelBlue << "\n";
    }
  }

  return 0;
}

