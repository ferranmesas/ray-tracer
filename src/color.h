#ifndef COLOR_H
#define COLOR_H

typedef struct {
    float h, s, l;
} color_hsl;

typedef struct {
    unsigned char r, g, b;
} color_rgb;

extern const color_rgb COLOR_SKY;

color_rgb hsl2rgb(const color_hsl hsl);

color_rgb blend_rgb(const color_rgb a, const color_rgb b, float amount);

#endif //RAY_TRACER_COLOR_H
