#ifndef POINT_H
#define POINT_H
#include <stdio.h>

typedef struct { float x, y, z; } point;

extern const point POINT_ZERO;

float distance(const point p, const point q);

void normalize(point *p);

float dot_product(const point p, const point q);

void print_point(const point p);

#endif // POINT_H
