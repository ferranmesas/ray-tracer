#ifndef POINT_H
#define POINT_H
#include <stdio.h>

#define POINT_STRUCT struct { float x, y, z; }
typedef POINT_STRUCT point;

float distance(point *p, point *q);

void print_point(point *p);

#endif // POINT_H
