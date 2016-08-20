#include "point.h"
#include "math.h"

const point POINT_ZERO = {0.0f, 0.0f, 0.0f};

float distance(const point *p, const point *q) {
    return sqrt(
      (p->x - q->x) * (p->x - q->x) +
      (p->y - q->y) * (p->y - q->y) +
      (p->z - q->z) * (p->z - q->z)
    );
}

void normalize(point *p) {
  float length = distance(p, &POINT_ZERO);
  p->x /= length;
  p->y /= length;
  p->z /= length;
}

float dot_product(const point p, const point q) {
    return p.x * q.x + p.y * q.y + p.z * q.z;
}

void print_point (const point *p){
 fprintf(stderr, "(%f, %f, %f)\n", p->x, p->y, p->z);
}
