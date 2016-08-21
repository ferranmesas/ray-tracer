#include <stdio.h>
#include <stdlib.h>
#include "image.h"

void init_image(image *im, int width, int height) {
  im->width = width;
  im->height = height;
  im->data = (char*) malloc(sizeof(char) * width * height);
}

void destroy_image(image *im) {
  free(im->data);
}

void print_image(image *im) {
  printf("P5\n%ld %ld\n255\n", im->width, im->height);
  for(int i = 0; i < im->width * im->height; i++) {
    putchar(im->data[i]);
  }
}

void image_set_pixel(image *im, int i, int j, char value) {
  im->data[i * im->width + j] = value;

}
