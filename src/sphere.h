#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"

typedef struct {
  point center;
  float r;
} sphere;

float sphere_distance(const sphere s, const point p);
#endif // SPHERE_H
