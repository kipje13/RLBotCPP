#pragma once

#include "renderer.h"

#include <string>

namespace rlbot {
class NamedRenderer : public Renderer {
public:
  NamedRenderer(std::string name);
  void FinishAndSend();
};
} // namespace rlbot
