#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "image.h"
#include "sphere.h"
#include "point.h"
#include "ray.h"

#define EPS 1.0E-3
#define MAX_ITER 100
#define N_RAYS 64

int intersects(ray r, sphere *spheres, int n_spheres, ray *normal);

int main(int argc, char* argv[]) {
  srand(time(NULL));
  long height, width, min_dim;
  if(argc == 3) {
    width = strtol(argv[1], NULL, 10);
    height = strtol(argv[2], NULL, 10);
  }
  else {
    width = 100;
    height = 100;
  }

  min_dim = height < width ? height : width;

  image *im = (image*) malloc(sizeof(image));
  init_image(im, width, height);

  point camera, dir, light_source;
  scanf("%f %f %f\n", &(camera.x), &(camera.y), &(camera.z));
  scanf("%f %f %f\n", &(dir.x), &(dir.y), &(dir.z));
  scanf("%f %f %f\n", &(light_source.x), &(light_source.y), &(light_source.z));

  int n_spheres;
  scanf("%d\n", &n_spheres);

  sphere *spheres = (sphere*) malloc(n_spheres * sizeof(sphere));
  for (int i = 0; i < n_spheres; i++) {
    sphere *s = (spheres + i);
    scanf("%f %f %f %f\n", &(s->x), &(s->y), &(s->z), &(s->r));
  }

  // Done reading input, start tracing!

  for (int i = 0; i < im->height; i++) {
    for (int j = 0; j < im->width; j++) {
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

        ray normal;

        if (intersects(current_ray, spheres, n_spheres, &normal)) {
          ray light;
          ray_from_to(&light, light_source, normal.source);

          float light_incidence = dot_product(normal.dir, light.dir);
          total_light += light_incidence > 0? light_incidence : 0;
        }
        im->data[i * im->width + j] = 32 + 224 * (total_light / N_RAYS);
      }
    }
  }

  print_image(im);
  destroy_image(im);
}

int intersects(ray r, sphere *spheres, int n_spheres, ray *normal) {
  for (int i = 0; i < MAX_ITER; i++){
    // find closest sphere and distance to it.
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
  }
  return 0;
}
