#include <math.h>

#include "color.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


const color_rgb COLOR_SKY = {198, 222, 255};

// Code from http://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion

color_rgb hsl2rgb(const color_hsl hsl) {
  color_rgb result = {

  };

  return result;
}

color_rgb blend_rgb(const color_rgb a, const color_rgb b, float amount) {
  color_rgb blended = {
    .r = (a.r * (1.0f - amount) + b.r * amount),
    .g = (a.g * (1.0f - amount) + b.g * amount),
    .b = (a.b * (1.0f - amount) + b.b * amount),
  };
  return blended;
}
