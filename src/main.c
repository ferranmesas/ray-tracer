#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "sphere.h"
#include "point.h"
#include "ray.h"

#define EPS 1.0E-3
#define MAX_ITER 100
#define MAX_DIST 100
#define N_RAYS 16

int intersects(ray r, sphere *spheres, int n_spheres, ray *normal);

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

  int n_spheres;
  scanf("%d\n", &n_spheres);

  sphere *spheres = (sphere*) malloc(n_spheres * sizeof(sphere));
  for (int i = 0; i < n_spheres; i++) {
    point center;
    float radius;
    scanf("%f %f %f %f\n", &center.x, &center.y, &center.z, &radius);
    spheres[i].center = center;
    spheres[i].r = radius;
  }

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

        ray normal, light, reflection, light_reflection;
        if (intersects(current_ray, spheres, n_spheres, &normal)) {
          ray_from_to(&light, light_source, normal.source);

          ray_reflect(current_ray, normal, &reflection);
          ray_reflect(light, normal, &light_reflection);


          float diffuse_light = max(0, dot_product(normal.dir, light.dir));
          float specular_light = max(0, -dot_product(light_reflection.dir, current_ray.dir));
          total_light += 0.1 + 0.5 * diffuse_light + 0.4 * pow(specular_light, 30);
        }
      }
      putchar(255 * total_light / N_RAYS);
    }
  }
}

int intersects(ray r, sphere *spheres, int n_spheres, ray *normal) {
  point ray_source = r.source;
  for (int i = 0; i < MAX_ITER; i++){
    // find closest sphere and the normal
    float min_dist = INFINITY;
    for (int k = 0; k < n_spheres; k++) {
      float dist = sphere_distance(spheres[k], r.source);
      if (dist < min_dist) {
        min_dist = dist;
        ray_from_to(normal, spheres[k].center, r.source);
        ray_reverse(normal);
      }
    }
    // advance the minimum distance.
    ray_advance(&r, min_dist);

    // we got real close to an object (there was an intersection)
    if (min_dist < EPS) {
      return 1;
    }
    // We went too far away of the original ray
    if (distance(ray_source, r.source) > MAX_DIST) {
      return 0;
    }
  }
  return 0;
}
