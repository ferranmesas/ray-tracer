#ifndef RAY_H
#define RAY_H

#include "point.h"

typedef struct {
  point source;
  point dir;
} ray;

void ray_from_to(ray * r, const point from, const point to);

void ray_advance(ray *r, float dist);

void ray_reverse(ray *r);


#endif // RAY_H
