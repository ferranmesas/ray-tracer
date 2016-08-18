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
  point *camera = (camera*) malloc(sizeof(point));
  point *direction = (camera*) malloc(sizeof(point));

  scanf("%f %f %f\n", &(camera->x), &(camera->y), &(camera->z));
  scanf("%f %f %f\n", &(direction->x), &(direction->y), &(direction->z));

  int n_spheres;
  scanf("%ld", &nspheres);

  print_point(camera);
  print_point(direction);
ima
  for(int i = 0; i < im->height; i++) {
    for(int j = 0; j < im->width; j++) {
      im->data[i * im->width + j] = j % 256;
    }
  }

  //print_image(im);
  destroy_image(im);
}
