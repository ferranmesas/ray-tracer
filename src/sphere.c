#include <stdio.h>

#include "sphere.h"
#include "point.h"

void read_sphere(sphere *s, FILE *fp) {
  point center;
  float radius;
  fscanf(fp, "%f %f %f %f\n", &center.x, &center.y, &center.z, &radius);
  s->center = center;
  s->r = radius;
}

float sphere_distance(const sphere s, const point p) {
  return distance(s.center, p) - s.r;
}
