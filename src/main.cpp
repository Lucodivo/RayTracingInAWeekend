#include <iostream>
#include "vec3.h"
#include "ray.h"

const int pixelWidth = 200;
const int pixelHeight = 100;
const vec3 eyeOrigin = vec3(0.0, 0.0, 0.0);
const vec3 bottomLeftCorner = vec3(-2.0, -1.0, -1.0);
const float width = 4.0;
const float height = 2.0;

const vec3 sphereCenter = vec3(0.0, 0.0, -1.0);
const float sphereRadius = 0.5;
const vec3 sphereColor = vec3(1.0, 0.0, 0.0);

vec3 missColor(const ray& r) {
  vec3 normalizedDir = normalize(r.dir());
  float t = 0.5*(normalizedDir.y() + 1.0);
  return ((1.0 - t) * vec3(1.0, 1.0, 1.0)) + (t * vec3(0.5, 0.7, 1.0));
}

float hitSphere(const vec3 &center, float radius, const ray &r) {
  vec3 centerToOrigin = r.origin() - center;
  float a = dot(r.dir(), r.dir());
  float b = 2.0 * dot(centerToOrigin, r.dir());
  float c = dot(centerToOrigin, centerToOrigin) - radius * radius;
  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) return -1.0;
  return (-b - sqrt(discriminant)) / (2.0 * a);
}

vec3 color(const ray& r) {
  float t = hitSphere(sphereCenter, sphereRadius, r);
  if(t != -1.0) {
    vec3 normal = normalize(r.at(t) - sphereCenter);
    normal += 1.0;
    normal *= 0.5;
    return normal;
  }
  return missColor(r);
}

int main()
{
  // ppm header: P3 means colors are in ascii, dimens are pixelWidth by pixelHeight, each pixel ranges from 0-255
  std::cout << "P3\n" << pixelWidth << " " << pixelHeight << "\n255\n";

  for(int pixelY = pixelHeight - 1; pixelY > -1; --pixelY) {
    for(int pixelX = 0; pixelX < pixelWidth; ++pixelX ) {
      float u = float(pixelX) / float(pixelWidth);
      float v = float(pixelY) / float(pixelHeight);
      ray r(eyeOrigin, bottomLeftCorner + vec3(u * width, v * height, 0.0));
      vec3 col = color(r);
      int pixelRed = int(255.99 * col.r());
      int pixelGreen = int(255.99 * col.g());
      int pixelBlue = int(255.99 * col.b());

      std::cout << pixelRed << " " << pixelGreen << " " << pixelBlue << "\n";
    }
  }

  return 0;
}
