#include "point.h"
#include "sphere.h"
#include "ray.h"

void ray_advance(ray *r, float dist) {
  r->source.x += r->dir.x * dist;
  r->source.y += r->dir.y * dist;
  r->source.z += r->dir.z * dist;
}
