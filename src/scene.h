#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "ray.h"
#include "material.h"


typedef struct {
  lua_State *L;
  point light_source;
} scene;

void read_scene(scene *s, const char *filename);

float scene_distance(const scene s, const point p);

int scene_get_intersection(const scene s, const ray incident_ray, point *intersection);

ray scene_get_normal(const scene s, const point p);

material scene_get_material(const scene s, const point p);

float scene_get_light(const scene s, const ray incident_ray, const ray normal, float reflectivity);

void free_scene(scene *s);

#endif // SCENE_H
