#pragma once

#include "namedrenderer.h"

#include <string>

namespace rlbotcpp {
class ScopedRenderer : public NamedRenderer {
public:
  ScopedRenderer(std::string name);
  ~ScopedRenderer();

  ScopedRenderer &operator=(const ScopedRenderer &) = delete;
  ScopedRenderer(const ScopedRenderer &) = delete;
};
} // namespace rlbotcpp
