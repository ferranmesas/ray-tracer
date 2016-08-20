#ifndef RAY_H
#define RAY_H

#include "point.h"

typedef struct {
  point source;
  point dir;
} ray;

void ray_advance(ray *r, float dist);
#endif // RAY_H
