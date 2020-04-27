#pragma once

#include <random>

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define PI 3.141592f

std::default_random_engine randomGenerator;
std::uniform_real_distribution<float> randomFractionDistribution(0.0f, 1.0f);

inline float randomFraction() {
  return randomFractionDistribution(randomGenerator);
}

Vec3 randomPointInUnitSphere() {
  Vec3 randomPoint;
  do{
    randomPoint = (Vec3(randomFraction(), randomFraction(), randomFraction()) * 2.0) - Vec3(1.0, 1.0, 1.0);
  } while(randomPoint.lengthSquared() >= 1.0);
  return randomPoint;
}

Vec3 randomPointInUnitDisk() {
  Vec3 randomPoint;
  do{
    randomPoint = (Vec3(randomFraction(), randomFraction(), 0.0) * 2.0) - Vec3(1.0, 1.0, 0.0);
  } while(randomPoint.lengthSquared() >= 1.0);
  return randomPoint;
}