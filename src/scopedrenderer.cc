#include "rlbot/scopedrenderer.h"

namespace rlbot {
ScopedRenderer::ScopedRenderer(std::string name) : NamedRenderer(name) {}

ScopedRenderer::~ScopedRenderer() { FinishAndSend(); }
} // namespace rlbot
