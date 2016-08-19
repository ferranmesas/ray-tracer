#ifndef RAY_H
#define RAY_H

typedef struct {
  point source;
  point direction;
} ray;

int intersect_sphere(ray *r, sphere *s, ray *normal);

#endif // RAY_H
