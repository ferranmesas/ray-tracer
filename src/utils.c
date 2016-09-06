#include "utils.h"

float max(const float a, const float b) {
  return a > b ? a : b;
}

float min(const float a, const float b) {
  return a < b ? a : b;
}

float clamp(const float value, const float lower, const float upper) {
  return max(lower, min(upper, value));
}
