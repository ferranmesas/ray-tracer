#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include "sphere.h"
#include "ray.h"

typedef struct {
  int n_spheres;
  sphere* spheres;
} scene;

void read_scene(scene *s, FILE *f);

float scene_distance(const scene s, const point p);

void scene_get_normal(const scene s, const point p, ray * normal);

void free_scene(scene *s);

#endif // SCENE_H
