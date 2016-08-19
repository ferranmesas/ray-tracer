#ifndef POINT_H
#define POINT_H
#include <stdio.h>

#define POINT_STRUCT struct { float x, y, z; }
typedef POINT_STRUCT point;

extern const point POINT_ZERO;

float distance(const point *p, const point *q);

void normalize(point *p);

void print_point(const point *p);

#endif // POINT_H
