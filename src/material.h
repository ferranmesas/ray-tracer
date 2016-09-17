#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

typedef struct {
  color col;
  float reflectivity;
} material;

#endif // MATERIAL_H
