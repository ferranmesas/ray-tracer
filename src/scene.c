#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "ray.h"

#define EPS 1.0E-3

void read_scene(scene *s, FILE *f) {
  fscanf(f, "%d\n", &s->n_spheres);

  s->spheres = (sphere*) malloc(s->n_spheres * sizeof(sphere));
  for (int i = 0; i < s->n_spheres; i++) {
    point center;
    float radius;
    scanf("%f %f %f %f\n", &center.x, &center.y, &center.z, &radius);
    s->spheres[i].center = center;
    s->spheres[i].r = radius;
  }
}

float scene_distance(const scene s, const point p) {
  float min_dist = INFINITY;
  for (int k = 0; k < s.n_spheres; k++) {
    float dist = sphere_distance(s.spheres[k], p);
    if (dist < min_dist) {
      min_dist = dist;
    }
  }
  return min_dist;
}

void scene_get_normal(const scene s, const point p, ray * normal) {
  normal->source = p;
  point a = p, b = p;
  a.x -= EPS / 2;
  b.x += EPS / 2;
  normal->dir.x = scene_distance(s, a) - scene_distance(s, b);
  a = b = p;
  a.y -= EPS / 2;
  b.y += EPS / 2;
  normal->dir.y = scene_distance(s, a) - scene_distance(s, b);
  a = b = p;
  a.z -= EPS / 2;
  b.z += EPS / 2;
  normal->dir.z = scene_distance(s, a) - scene_distance(s, b);

  normalize(&normal->dir);
}

void free_scene(scene *s) {
  free(s->spheres);
}
