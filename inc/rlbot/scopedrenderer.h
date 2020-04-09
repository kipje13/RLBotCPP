#pragma once

#include "rlbot/namedrenderer.h"

#include <string>

namespace rlbot {
class ScopedRenderer : public NamedRenderer {
public:
  ScopedRenderer(std::string name);
  ~ScopedRenderer();

  ScopedRenderer &operator=(const ScopedRenderer &) = delete;
  ScopedRenderer(const ScopedRenderer &) = delete;
};
} // namespace rlbot
