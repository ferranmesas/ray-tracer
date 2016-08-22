#ifndef PLANE_H
#define PLANE_H

#include <stdio.h>

#include "point.h"
#include "ray.h"

typedef struct {
  float a, b, c, d;
} plane;

void read_plane(plane *pl, FILE *fp);

void plane_get_normal(const plane pl, ray *normal);

float plane_distance(const plane pl, const point p);
#endif // PLANE_H
