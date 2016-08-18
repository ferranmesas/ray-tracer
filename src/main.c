#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "sphere.h"
#include "point.h"

int main(int argc, char* argv[]) {
  long height, width;
  if(argc == 3) {
    width = strtol(argv[1], NULL, 10);
    height = strtol(argv[2], NULL, 10);
  }
  else {
    width = 100;
    height = 100;
  }

  image *im = (image*) malloc(sizeof(image));
  init_image(im, width, height);
  point *camera = (point*) malloc(sizeof(point));
  point *direction = (point*) malloc(sizeof(point));

  scanf("%f %f %f\n", &(camera->x), &(camera->y), &(camera->z));
  scanf("%f %f %f\n", &(direction->x), &(direction->y), &(direction->z));

  int n_spheres;
  scanf("%d\n", &n_spheres);

  sphere *spheres = (sphere*) malloc(n_spheres * sizeof(sphere));
  for (int i = 0; i < n_spheres; i++) {
    sphere *s = (spheres + i);
    scanf("%f %f %f %f\n", &(s->x), &(s->y), &(s->z), &(s->r));
  }
  print_point(camera);
  print_point(direction);

  for(int i = 0; i < im->height; i++) {
    float u = 2.0f * i / (height-1) - 1;
    for(int j = 0; j < im->width; j++) {
      float v = 2.0f * j / (width - 1) - 1;

      im->data[i * im->width + j] = j % 256;
    }
  }

  print_image(im);
  destroy_image(im);
}
