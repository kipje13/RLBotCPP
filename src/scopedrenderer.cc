#include "scopedrenderer.h"

namespace rlbotcpp {
ScopedRenderer::ScopedRenderer(std::string name) : NamedRenderer(name) {}

ScopedRenderer::~ScopedRenderer() { FinishAndSend(); }
} // namespace rlbotcpp
