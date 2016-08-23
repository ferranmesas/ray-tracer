#ifndef COLOR_H
#define COLOR_H

typedef struct {
    float h, s, l;
} color_hsl;

typedef struct {
    char r, g, b;
} color_rgb;

void hsl2rgb(const color_hsl hsl, color_rgb *rgb);



#endif //RAY_TRACER_COLOR_H
