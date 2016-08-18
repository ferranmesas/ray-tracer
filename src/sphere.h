#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"

typedef struct {
  float x, y, z;
  float r;
} sphere;

float distance(sphere *s, point *p);

#endif // SPHERE_H
