#include "point.h"
#include "sphere.h"
#include "ray.h"

void ray_advance(ray *r, float dist) {
  r->source.x += r->dir.x * dist;
  r->source.y += r->dir.y * dist;
  r->source.z += r->dir.z * dist;
}

void ray_from_to(ray * r, const point from, const point to) {
  r->source = from;
  r->dir.x = to.x - from.x;
  r->dir.y = to.y - from.y;
  r->dir.z = to.z - from.z;
  normalize(&(r->dir));

}
