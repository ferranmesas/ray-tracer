#ifndef RAY_H
#define RAY_H

#include "point.h"

typedef struct {
  point source;
  point dir;
} ray;

void ray_from_to(ray *r, const point from, const point to);

void ray_advance(ray *r, float dist);

void ray_reverse(ray *r);

void ray_reflect(ray *reflection, const ray r, const ray normal);


#endif // RAY_H
