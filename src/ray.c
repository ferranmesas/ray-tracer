#include "point.h"
#include "ray.h"

void ray_from_to(ray * r, const point from, const point to) {
  r->source = from;
  r->dir.x = to.x - from.x;
  r->dir.y = to.y - from.y;
  r->dir.z = to.z - from.z;
  normalize(&(r->dir));
}

void ray_advance(ray *r, float dist) {
  r->source.x += r->dir.x * dist;
  r->source.y += r->dir.y * dist;
  r->source.z += r->dir.z * dist;
}

void ray_reverse(ray *r) {
  r->dir.x = -r->dir.x;
  r->dir.y = -r->dir.y;
  r->dir.z = -r->dir.z;
}

void ray_reflect(ray *reflection, const ray r, const ray normal) {
  reflection->source = normal.source;
  float dot = dot_product(r.dir, normal.dir);
  reflection->dir.x = r.dir.x - 2 * normal.dir.x * dot;
  reflection->dir.y = r.dir.y - 2 * normal.dir.y * dot;
  reflection->dir.z = r.dir.z - 2 * normal.dir.z * dot;
  normalize(&reflection->dir);
}
