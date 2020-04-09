#include "rlbot/color.h"

namespace rlbot {
Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
  r = red;
  g = green;
  b = blue;
  a = alpha;
}

const Color Color::red = Color(0xFF, 0x00, 0x00, 0xFF);
const Color Color::green = Color(0x00, 0xFF, 0x00, 0xFF);
const Color Color::blue = Color(0x00, 0x00, 0xFF, 0xFF);

const Color Color::yellow = Color(0xFF, 0xFF, 0x00, 0xFF);
const Color Color::magenta = Color(0xFF, 0x00, 0xFF, 0xFF);
const Color Color::cyan = Color(0x00, 0xFF, 0xFF, 0xFF);

const Color Color::black = Color(0x00, 0x00, 0x00, 0xFF);
const Color Color::white = Color(0xFF, 0xFF, 0xFF, 0xFF);
} // namespace rlbot
