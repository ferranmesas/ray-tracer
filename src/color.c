#include <stdio.h>
#include "color.h"

const color_rgb COLOR_SKY = {198, 222, 255};

// Code from http://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
static float hue2rgb(float p, float q, float t) {
  while(t < 0) t++;
  while(t > 1) t--;
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
  if(t < 1.0f/2.0f) return q;
  if(t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
  return p;
}

void hsl2rgb(const color_hsl hsl, color_rgb *rgb) {
  if(hsl.s == 0) {
    rgb->r = 255 * hsl.l;
    rgb->g = 255 * hsl.l;
    rgb->b = 255 * hsl.l;
    return;
  }

  float q = hsl.l < 0.5 ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
  float p = 2 * hsl.l - q;
  rgb->r = 255 * hue2rgb(p, q, hsl.h + 1.0f/3.0f);
  rgb->g = 255 * hue2rgb(p, q, hsl.h);
  rgb->b = 255 * hue2rgb(p, q, hsl.h - 1.0f/3.0f);
}

color_rgb blend_rgb(const color_rgb a, const color_rgb b, float amount) {
  color_rgb blended = {
    .r = (a.r * (1.0f - amount) + b.r * amount),
    .g = (a.g * (1.0f - amount) + b.g * amount),
    .b = (a.b * (1.0f - amount) + b.b * amount),
  };
  return blended;
}
