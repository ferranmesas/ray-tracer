#include "point.h"

void print_point (point *p){
 fprintf(stderr, "(%f, %f, %f)\n", p->x, p->y, p->z);
}
