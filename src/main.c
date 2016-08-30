#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "defines.h"

#include "sphere.h"
#include "point.h"
#include "ray.h"
#include "scene.h"
#include "color.h"
#include "utils.h"

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

  point camera, dir;
  scanf("%f %f %f\n", &(camera.x), &(camera.y), &(camera.z));
  scanf("%f %f %f\n", &(dir.x), &(dir.y), &(dir.z));

  scene s;

  read_scene(&s, stdin);
  // Done reading input, start tracing!

  // netpbm header
  printf("P6\n%d %d\n255\n", width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // both u and v are scaled by the same value (min_dim) in order to preserve
      // the aspect ratio.
      float u = 2.0f * i / (min_dim - 1) - (1.0f * height / min_dim);
      float v = 2.0f * j / (min_dim - 1) - (1.0f * width / min_dim);


      color final_color = {0, 0, 0};
      float final_fog_amount = 0.0f;
      float final_light_amount = 0.0f;

      for (int k = 0; k < N_RAYS; k ++) {

        // TODO: Calculate proper ray source and direction for each pixel!
        #if N_RAYS > 1
        float pixel_eps = 2.0f / (min_dim - 1);
        point pixel = {
          u + pixel_eps * (1.0f * rand() / RAND_MAX - 0.5),
          length(dir),
          v + pixel_eps * (1.0f * rand() / RAND_MAX - 0.5)
        };
        #else
        point pixel = {
          u,
          length(dir),
          v
        };
        #endif

        ray current_ray;
        ray_from_to(&current_ray, pixel, camera);
        ray_reverse(&current_ray);

        color ray_color = {0, 0, 0};
        float ray_light_amount = 0.0f;
        float ray_fog_amount = 0.0f;

        point intersection;
        ray normal;
        ray reflection;

        if (scene_get_intersection(s, current_ray, &intersection)) {
          normal = scene_get_normal(s, intersection);
          ray_color = scene_get_color(s, intersection);
          ray_light_amount = scene_get_light(s, current_ray, normal);

          ray_reflect(&reflection, current_ray, normal);

          // We calculate diffuse light first because it tells us if the light
          // is visible from the point. If it is, we'll need to calculate shadows,
          // specular lights, etc.

          ray_fog_amount = distance(camera, intersection) / MAX_DIST;
        }
        final_color = color_add(final_color, ray_color);
        final_fog_amount += ray_fog_amount;
        final_light_amount += ray_light_amount;
      }

      final_fog_amount /= N_RAYS;
      final_light_amount = final_light_amount / N_RAYS;


      final_color = color_multiply(final_color, 1.0f / N_RAYS);

      final_color = color_multiply(final_color, final_light_amount);

      if(final_light_amount > 1) {
        final_color = color_blend(final_color, COLOR_WHITE, final_light_amount - 1);
      }

      final_color = color_blend(final_color, COLOR_SKY, final_fog_amount);

      putchar(255 * clamp(final_color.r, 0.0f, 1.0f));
      putchar(255 * clamp(final_color.g, 0.0f, 1.0f));
      putchar(255 * clamp(final_color.b, 0.0f, 1.0f));
    }
  }
}
