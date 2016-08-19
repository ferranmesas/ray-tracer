#include "point.h"
#include "math.h"

float distance(point *p, point *q) {
    return sqrt(
      (p->x - q->x) * (p->x - q->x) +
      (p->y - q->y) * (p->y - q->y) +
      (p->z - q->z) * (p->z - q->z)
    );
}

void print_point (point *p){
 fprintf(stderr, "(%f, %f, %f)\n", p->x, p->y, p->z);
}
