#include "math.h"
#include "sphere.h"

float distance(sphere *s, point *p) {
  float dist_to_center = sqrt(
    (p->x - s->x) * (p->x - s->x) +
    (p->y - s->y) * (p->y - s->y) +
    (p->z - s->z) * (p->z - s->z)
  );
  return dist_to_center - s->r;
}
