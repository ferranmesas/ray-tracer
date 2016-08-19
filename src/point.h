#ifndef POINT_H
#define POINT_H
#include <stdio.h>

typedef struct {
  float x, y, z;
} point;

float distance(point *p, point *q);

void print_point(point *p);

#endif // POINT_H
