#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "sphere.h"
#include "point.h"
#include "ray.h"
#include "scene.h"

#define EPS 1.0E-3
#define MAX_ITER 512
#define MAX_DIST 100.0f
#define N_RAYS 4

int intersects(ray r, const scene s, point *intersection);

float max(float a, float b) {
  return a > b ? a : b;
}

float min(float a, float b) {
  return a < b ? a : b;
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
  printf("P5\n%d %d\n255\n", width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // both u and v are scaled by the same value (min_dim) in order to preserve
      // the aspect ratio.
      float u = 2.0f * i / (min_dim - 1) - (1.0f * height / min_dim);
      float v = 2.0f * j / (min_dim - 1) - (1.0f * width / min_dim);
      float pixel_eps = 2.0f / (min_dim - 1);

      float total_light = 0;
      for (int k = 0; k < N_RAYS; k ++) {
        // TODO: Calculate proper ray source and direction for each pixel!
        // need to adjust for perspective
        ray current_ray = {
          .source = camera,
          .dir = {
            u + pixel_eps * ((float) rand() / RAND_MAX - 0.5),
            10,
            v + pixel_eps * ((float) rand() / RAND_MAX - 0.5)
          }
        };
        normalize(&current_ray.dir);

        point intersection;
        ray normal, light, reflection, light_reflection;
        if (intersects(current_ray, s, &intersection)) {
          scene_get_normal(s, intersection, &normal);
          float fog_amount = distance(camera, normal.source) / MAX_DIST;
          ray_from_to(&light, light_source, normal.source);

          ray_reflect(current_ray, normal, &reflection);
          ray_reflect(light, normal, &light_reflection);

          float diffuse_light = max(0, dot_product(normal.dir, light.dir));
          float specular_light = max(0, -dot_product(light_reflection.dir, current_ray.dir));
          float light = 0.1 + 0.6 * diffuse_light + 0.3 * pow(specular_light, 10);
          total_light += fog_amount * 0.8 + (1 - fog_amount) * light;
        }
      }
      putchar(255 * total_light / N_RAYS);
    }
  }
}

int intersects(ray r, const scene s, point *intersection) {
  point ray_source = r.source;
  for (int i = 0; i < MAX_ITER; i++){
    // find closest sphere and the normal
    float min_dist = scene_distance(s, r.source);
    // we got real close to an object (there was an intersection)
    if (min_dist < EPS) {
      *intersection = r.source;
      return 1;
    }
    // We went too far away of the original ray
    if (distance(ray_source, r.source) > MAX_DIST) {
      return 0;
    }
    ray_advance(&r, min_dist);
  }
  return 0;
}
