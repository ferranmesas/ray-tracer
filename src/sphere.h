#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"

typedef struct {
  union {
    point center;
    struct {
      float x, y, z;
    };
  };
  float r;
} sphere;

float sphere_distance(sphere *s, point *p);

#endif // SPHERE_H
