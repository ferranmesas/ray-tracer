#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "defines.h"

#include "point.h"
#include "ray.h"
#include "scene.h"
#include "color.h"
#include "utils.h"
#include "material.h"

color ray_march(const scene s, const ray r, const int max_reflections);

float triangular_noise();

int main(int argc, char* argv[]) {
  srand(time(NULL));
  int height, width, min_dim;
  if(argc == 3) {
    width = strtol(argv[1], NULL, 10);
    height = strtol(argv[2], NULL, 10);
  }
  else {
    width = 100;
    height = 100;
  }

  min_dim = height < width ? height : width;

  point camera = {
    0,
    -1,
    0
  };

  scene s;

  read_scene(&s, "scene.lua");
  // Done reading input, start tracing!

  // netpbm header
  printf("P6\n%d %d\n255\n", width, height);
  for (int i = 0; i < height; i++) {
    fprintf(stderr, "%d / %d\n", i, height);
    for (int j = 0; j < width; j++) {
      // both u and v are scaled by the same value (min_dim) in order to preserve
      // the aspect ratio.
      float u = 2.0f * i / (min_dim - 1) - (1.0f * height / min_dim);
      float v = 2.0f * j / (min_dim - 1) - (1.0f * width / min_dim);

      color final_color = COLOR_BLACK;

      for (int k = 0; k < N_RAYS; k ++) {
        //fprintf(stderr, "%d, %d, %d\n", i, j, k);

        // TODO: Calculate proper ray source and direction for each pixel!

        #if N_RAYS > 1
        float pixel_eps = 1.0f / (min_dim - 1);
        #else
        float pixel_eps = 0.0f;
        #endif
        point pixel = {
          u + pixel_eps * triangular_noise(),
          0,
          v + pixel_eps * triangular_noise()
        };

        ray current_ray;
        ray_from_to(&current_ray, pixel, camera);
        ray_reverse(&current_ray);

        if(scene_distance(s, current_ray.source) < 0) {
          fprintf(stderr, "Image plane intersects scene!\n");
          continue;
        }
        color ray_color = ray_march(s, current_ray, MAX_REFLECTIONS);

        final_color = color_add(final_color, ray_color);
      }

      final_color = color_multiply(final_color, 1.0f / N_RAYS);

      putchar(255 * clamp(final_color.r, 0.0f, 1.0f));
      putchar(255 * clamp(final_color.g, 0.0f, 1.0f));
      putchar(255 * clamp(final_color.b, 0.0f, 1.0f));
    }
  }
  free_scene(&s);
}

color ray_march(const scene s, const ray r, const int max_reflections) {
  point ray_source = r.source;
  if (!max_reflections) {
    return COLOR_BLACK;
  }

  point intersection = {0, 0, 0};

  if (!scene_get_intersection(s, r, &intersection)) {
    return COLOR_SKY;
  }

  ray normal = scene_get_normal(s, intersection);
  material mat = scene_get_material(s, intersection);

  float ray_light = scene_get_light(s, r, normal, mat.reflectivity);
  float ray_fog = distance(ray_source, intersection) / MAX_DIST;

  color this_color = color_bake(mat.col, ray_light, ray_fog);

  ray reflection;
  ray_reflect(&reflection, r, normal);
  ray_advance(&reflection, EPS);

  color reflection_color = ray_march(s, reflection, max_reflections - 1);

  return color_blend(this_color, reflection_color, mat.reflectivity);
}

float triangular_noise() {
  return ((float) rand() / RAND_MAX) + ((float) rand() / RAND_MAX) - 1.0f;
}
