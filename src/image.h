#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
  long width;
  long height;
  char *data;
} image;

void init_image(image *im, long width, long height);
void destroy_image(image *im);
void print_image(image *im);

#endif // IMAGE_H
