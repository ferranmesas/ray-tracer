#ifndef COLOR_H
#define COLOR_H

typedef struct {
    float r, g, b;
} color;

extern const color COLOR_WHITE;
extern const color COLOR_BLACK;

extern const color COLOR_SKY;

color color_blend(const color a, const color b, float amount);

color color_add(const color a, const color b);

color color_multiply(const color c, float value);


#endif //RAY_TRACER_COLOR_H
