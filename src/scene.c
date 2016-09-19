#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "defines.h"
#include "scene.h"
#include "ray.h"
#include "material.h"
#include "color.h"
#include "utils.h"

static void stackDump (lua_State *L) {
      int i;
      int top = lua_gettop(L);
      fprintf(stderr, "lua stack:\n");
      for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
          case LUA_TSTRING:  /* strings */
            fprintf(stderr, "`%s'\n", lua_tostring(L, i));
            break;

          case LUA_TBOOLEAN:  /* booleans */
            fprintf(stderr, lua_toboolean(L, i) ? "true\n" : "false\n");
            break;

          case LUA_TNUMBER:  /* numbers */
            fprintf(stderr, "%g\n", lua_tonumber(L, i));
            break;

          default:  /* other values */
            fprintf(stderr, "%s\n", lua_typename(L, t));
            break;

        }
        printf("  ");  /* put a separator */
      }
      printf("\n");  /* end the listing */
    }

int mymod(float f) {
  return fabsf(fmodf(floor(f), 2));
}

void bail(lua_State *L, char *msg){
  fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
          msg, lua_tostring(L, -1));
  exit(1);
}
void read_scene(scene *s, const char *filename) {
  s->L = luaL_newstate();
  luaL_openlibs(s->L);

  luaL_loadfile(s->L, filename);
  lua_pcall(s->L, 0, 0, 0);

  lua_getglobal(s->L, "light_source");
  lua_pushstring(s->L, "x");
  lua_gettable(s->L, -2);
  s->light_source.x = lua_tonumber(s->L, -1);
  lua_pop(s->L, 1);

  lua_pushstring(s->L, "y");
  lua_gettable(s->L, -2);
  s->light_source.y = lua_tonumber(s->L, -1);
  lua_pop(s->L, 1);

  lua_pushstring(s->L, "z");
  lua_gettable(s->L, -2);
  s->light_source.z = lua_tonumber(s->L, -1);
  lua_pop(s->L, 2);
}

float scene_distance(const scene s, const point p) {
  lua_getglobal(s.L, "scene");
  lua_pushnumber(s.L, p.x);
  lua_pushnumber(s.L, p.y);
  lua_pushnumber(s.L, p.z);
  lua_call(s.L, 3, 2);
  float min_dist = lua_tonumber(s.L, -2);
  lua_pop(s.L, 2);
  return min_dist;
}

int scene_get_intersection(const scene s, const ray incident_ray, point *intersection) {
  ray r = incident_ray;

  for (int i = 0; i < MAX_ITER; i++){
    float min_dist = scene_distance(s, r.source);

    if (min_dist < 0) {
      point inside = r.source;
      float dist_inside = scene_distance(s, inside);
      while(scene_distance(s, r.source) <= 0) {
        ray_advance(&r, -EPS);
      }
      point outside = r.source;
      float dist_outside = scene_distance(s, outside);

      float interp = dist_outside / (dist_outside - dist_inside);
      ray_advance(&r, interp * distance(inside, outside));
      *intersection = r.source;
      return 1;
    }
    if (min_dist < EPS) {
      min_dist = EPS;
    }
    if (distance(incident_ray.source, r.source) > MAX_DIST) {
      return 0;
    }
    ray_advance(&r, min_dist);
  }
  return 0;
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

material scene_get_material(const scene s, const point p) {

  lua_getglobal(s.L, "scene");
  lua_pushnumber(s.L, p.x);
  lua_pushnumber(s.L, p.y);
  lua_pushnumber(s.L, p.z);
  lua_call(s.L, 3, 2);

  lua_pushnumber(s.L, p.x);
  lua_pushnumber(s.L, p.y);
  lua_pushnumber(s.L, p.z);
  lua_call(s.L, 3, 1);

  lua_pushstring(s.L, "reflectivity");

  lua_gettable(s.L, -2);

  material result;
  result.reflectivity = lua_tonumber(s.L, -1);
  lua_pop(s.L, 1);

  lua_pushstring(s.L, "color");
  lua_gettable(s.L, -2);

  lua_pushnumber(s.L, 1);
  lua_gettable(s.L, -2);
  result.col.r = lua_tonumber(s.L, -1);
  lua_pop(s.L, 1);

  lua_pushnumber(s.L, 2);
  lua_gettable(s.L, -2);
  result.col.g = lua_tonumber(s.L, -1);
  lua_pop(s.L, 1);

  lua_pushnumber(s.L, 3);
  lua_gettable(s.L, -2);
  result.col.b = lua_tonumber(s.L, -1);
  lua_pop(s.L, 1);

  lua_settop(s.L, 1);

  return result;
}

float scene_get_light(const scene s, const ray incident_ray, const ray normal, const float reflectivity) {

  ray incident_light;
  ray_from_to(&incident_light, s.light_source, normal.source);

  float diffuse_light = max(0, dot_product(normal.dir, incident_light.dir));

  if (diffuse_light < 0) {
    return 0.15;
  }

  point light_intersection;
  scene_get_intersection(s, incident_light, &light_intersection);
  int is_shadow = distance(light_intersection, normal.source) > EPS;
  if (is_shadow) {
    return 0.15;
  }

  ray light_reflection;
  ray_reflect(&light_reflection, incident_light, normal);

  float specular_light = pow(max(0, -dot_product(light_reflection.dir, incident_ray.dir)), 15);
  return 0.15f + diffuse_light + reflectivity * specular_light;
}

void free_scene(scene *s) {
  lua_close(s->L);
}
