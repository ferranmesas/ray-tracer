#include <math.h>
#include <stdio.h>
#include "color.h"

const color COLOR_WHITE = {1, 1, 1};
const color COLOR_BLACK = {0, 0, 0};

const color COLOR_SKY = {0.775, 0.87, 1};

color color_bake(const color hue, const float light, const float fog) {
  color final_color = color_multiply(hue, light);
  if(light > 1) {
    final_color = color_blend(final_color, COLOR_WHITE, 2*(light - 1));
  }
  final_color = color_blend(final_color, COLOR_SKY, fog);

  return final_color;
}

color color_blend(const color a, const color b, const float amount) {
  color blended = {
    .r = (a.r * (1.0f - amount) + b.r * amount),
    .g = (a.g * (1.0f - amount) + b.g * amount),
    .b = (a.b * (1.0f - amount) + b.b * amount),
  };
  return blended;
}

color color_add(const color a, const color b) {
  color added = {
    .r = a.r + b.r,
    .g = a.g + b.g,
    .b = a.b + b.b,
  };
  return added;
}

color color_multiply(const color c, float value) {
  color multiplied = {
    .r = c.r * value,
    .g = c.g * value,
    .b = c.b * value,
  };
  return multiplied;
}
