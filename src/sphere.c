#include "math.h"
#include "sphere.h"
#include "point.h"

float sphere_distance(sphere *s, point *p) {
  return distance(&(s->center), p) - s->r;
}
