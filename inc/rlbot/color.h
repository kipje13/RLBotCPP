#pragma once

#include <cstdint>

namespace rlbot {
struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  static const Color red;
  static const Color green;
  static const Color blue;

  static const Color yellow;
  static const Color magenta;
  static const Color cyan;

  static const Color black;
  static const Color white;
};
} // namespace rlbot
