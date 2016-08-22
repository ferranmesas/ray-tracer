#include "plane.h"
#include "point.h"

void read_plane(plane *pl, FILE *fp) {
  fscanf(fp, "%f %f %f %f\n", &pl->a, &pl->b, &pl->c, &pl->d);
}

float plane_distance(const plane pl, const point p) {
  point plane_point = {
    .x = pl.a,
    .y = pl.b,
    .z = pl.c
  };
  return (pl.a * p.x + pl.b * p.y + pl.c *p.z + pl.d) / distance(plane_point, POINT_ZERO);
}