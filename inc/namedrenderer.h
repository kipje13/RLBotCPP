#pragma once

#include "renderer.h"

#include <string>

namespace rlbotcpp {
class NamedRenderer : public Renderer {
public:
  NamedRenderer(std::string name);
  void FinishAndSend();
};
} // namespace rlbotcpp
