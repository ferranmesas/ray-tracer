#ifndef POINT_H
#define POINT_H
#include <stdio.h>

typedef struct {
  float x, y, z;
} point;

void print_point(point *p) {
  printf("(%f, %f, %f)\n", p->x, p->y, p->z);
}
#endif // POINT_H
