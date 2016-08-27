#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "sphere.h"
#include "point.h"
#include "ray.h"
#include "scene.h"
#include "color.h"

#define EPS 1.0E-3
#define MAX_ITER 2048
#define MAX_DIST 100.0f
#define N_RAYS 1

int intersect(ray r, const scene s, point *intersection);

float max(float a, float b) {
  return a > b ? a : b;
}

float min(float a, float b) {
  return a < b ? a : b;
}

float clamp(float value, float lower, float upper) {
  return max(lower, min(upper, value));
}
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

  point camera, dir, light_source;
  scanf("%f %f %f\n", &(camera.x), &(camera.y), &(camera.z));
  scanf("%f %f %f\n", &(dir.x), &(dir.y), &(dir.z));
  scanf("%f %f %f\n", &(light_source.x), &(light_source.y), &(light_source.z));

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


        point intersection, light_intersection;
        ray normal, incident_light;
        ray reflection, light_reflection;
        if (intersect(current_ray, s, &intersection)) {
          normal = scene_get_normal(s, intersection);
          ray_color = scene_get_color(s, intersection);
          ray_from_to(&incident_light, light_source, normal.source);

          ray_reflect(&reflection, current_ray, normal);
          ray_reflect(&light_reflection, incident_light, normal);

          // We calculate diffuse light first because it tells us if the light
          // is visible from the point. If it is, we'll need to calculate shadows,
          // specular lights, etc.
          float diffuse_light = max(0, dot_product(normal.dir, incident_light.dir));

          intersect(incident_light, s, &light_intersection);
          int is_shadow = distance(light_intersection, intersection) > EPS;

          if(diffuse_light > 0 && !is_shadow) {
            float specular_light = pow(max(0, -dot_product(light_reflection.dir, current_ray.dir)), 15);
            ray_light_amount = 0.05 + diffuse_light + 0.5 * specular_light;

          } else {
            ray_light_amount = 0.05;
          }
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

int intersect(ray r, const scene s, point *intersection) {
  point ray_source = r.source;
  for (int i = 0; i < MAX_ITER; i++){
    // find closest sphere and the normal
    float min_dist = scene_distance(s, r.source);

    // we got real close to an object. advance slowly until we get inside.
    //fprintf(stderr, "%d, %f\n", i, min_dist);
    if (min_dist < 0) {
      // We are inside an object! let's find a point outside and linearly interpolate
      // to find the exct border of the object.
      point inside = r.source;
      double dist_inside = scene_distance(s, inside);
      while(scene_distance(s, r.source) <= 0) {
        ray_advance(&r, -EPS);
      }
      point outside = r.source;
      double dist_outside = scene_distance(s, outside);

      double interp = dist_outside / (dist_outside - dist_inside);
      ray_advance(&r, interp * distance(inside, outside));
      *intersection = r.source;
      return 1;
    }
    if (min_dist < EPS) {
      min_dist = EPS;
    }
    // We went too far away of the original ray
    if (distance(ray_source, r.source) > MAX_DIST) {
      return 0;
    }
    ray_advance(&r, min_dist);
  }
  return 0;
}
