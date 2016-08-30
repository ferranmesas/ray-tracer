#include "utils.h"

float max(float a, float b) {
  return a > b ? a : b;
}

float min(float a, float b) {
  return a < b ? a : b;
}

float clamp(float value, float lower, float upper) {
  return max(lower, min(upper, value));
}
