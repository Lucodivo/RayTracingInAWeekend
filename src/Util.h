#pragma once

#include <random>

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

std::default_random_engine randomGenerator;
std::uniform_real_distribution<float> randomFractionDistribution(0.0f, 1.0f);

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