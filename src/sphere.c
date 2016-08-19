#include "sphere.h"
#include "point.h"

float sphere_distance(const sphere *s, const point *p) {
  return distance(&(s->center), p) - s->r;
}
