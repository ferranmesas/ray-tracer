#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include "color.h"

typedef struct {
  point light_source;
  int n_spheres;
  sphere *spheres;
  int n_planes;
  plane *planes;
} scene;

void read_scene(scene *s, FILE *f);

float scene_distance(const scene s, const point p);

ray scene_get_normal(const scene s, const point p);

float scene_get_light(const scene s, const ray normal);

color scene_get_color(const scene s, const point p);

void free_scene(scene *s);

#endif // SCENE_H
