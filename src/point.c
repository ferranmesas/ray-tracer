#include "point.h"
#include "math.h"

const point POINT_ZERO = {0.0f, 0.0f, 0.0f};

float distance(const point p, const point q) {
    return sqrt(
      (p.x - q.x) * (p.x - q.x) +
      (p.y - q.y) * (p.y - q.y) +
      (p.z - q.z) * (p.z - q.z)
    );
}

float length(const point p) {
  return distance(p, POINT_ZERO);
}

void normalize(point *p) {
  float len = length(*p);
  p->x /= len;
  p->y /= len;
  p->z /= len;
}

float dot_product(const point p, const point q) {
    return p.x * q.x + p.y * q.y + p.z * q.z;
}

void print_point (const point p){
 fprintf(stderr, "(%f, %f, %f)\n", p.x, p.y, p.z);
}
