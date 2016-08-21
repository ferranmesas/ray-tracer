#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
  long width;
  long height;
  char *data;
} image;

void init_image(image *im, int width, int height);
void destroy_image(image *im);
void print_image(image *im);

void image_set_pixel(image *im, int i, int j, char value);

#endif // IMAGE_H
