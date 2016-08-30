#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include "color.h"
#include "utils.h"

#define EPS 1.0E-3

void read_scene(scene *s, FILE *fp) {

  fscanf(fp, "%f %f %f\n", &(s->light_source.x), &(s->light_source.y), &(s->light_source.z));

  fscanf(fp, "%d\n", &s->n_spheres);
  s->spheres = (sphere*) malloc(s->n_spheres * sizeof(sphere));
  for (int i = 0; i < s->n_spheres; i++) {
    read_sphere(&s->spheres[i], fp);
  }

  fscanf(fp, "%d\n", &s->n_planes);
  s->planes = (plane*) malloc(s->n_planes * sizeof(plane));
  for (int i = 0; i < s->n_planes; i++) {
    read_plane(&s->planes[i], fp);
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

  for (int k = 0; k < s.n_planes; k++) {
    float dist = plane_distance(s.planes[k], p);
    if (dist < min_dist) {
      min_dist = dist;
    }
  }

  return min_dist;
}

ray scene_get_normal(const scene s, const point p) {
  ray normal;
  normal.source = p;
  point a = p, b = p;
  a.x -= EPS / 2;
  b.x += EPS / 2;
  normal.dir.x = scene_distance(s, a) - scene_distance(s, b);
  a = b = p;
  a.y -= EPS / 2;
  b.y += EPS / 2;
  normal.dir.y = scene_distance(s, a) - scene_distance(s, b);
  a = b = p;
  a.z -= EPS / 2;
  b.z += EPS / 2;
  normal.dir.z = scene_distance(s, a) - scene_distance(s, b);

  normalize(&normal.dir);
  return normal;
}

float scene_get_light(const scene s, const ray normal) {

  ray incident_light;
  ray_from_to(&incident_light, s.light_source, normal.source);

  float diffuse_light = max(0, dot_product(normal.dir, incident_light.dir));

  if (diffuse_light < 0) {
    return 0.05;
  }

  point light_intersection;
  intersect(incident_light, s, &light_intersection);
  int is_shadow = distance(light_intersection, normal.source) > EPS;
  if (is_shadow) {
    return 0.05;
  }

  ray light_reflection;
  ray_reflect(&light_reflection, incident_light, normal);

  float specular_light = pow(max(0, -dot_product(light_reflection.dir, current_ray.dir)), 15);
  return 0.05 + diffuse_light + 0.5 * specular_light;
}

color scene_get_color(const scene s, const point p) {
  return (color) {0.7, 0, 0};

  for (int k = 0; k < s.n_spheres; k++) {
    float dist = sphere_distance(s.spheres[k], p);
    if (dist < EPS) {
      return (color) {1, 0, 0};
    }
  }

  for (int k = 0; k < s.n_planes; k++) {
    float dist = plane_distance(s.planes[k], p);
    if (dist < EPS) {
      return (color) {0, 1, 0};
    }
  }
}

void free_scene(scene *s) {
  free(s->spheres);
}
