#ifndef SPHERE_H
#define SPHERE_H

#include <stdio.h>

#include "point.h"

typedef struct {
  point center;
  float r;
} sphere;

void read_sphere(sphere *s, FILE *fp);

float sphere_distance(const sphere s, const point p);

#endif // SPHERE_H
