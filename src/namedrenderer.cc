#include "rlbot/namedrenderer.h"

#include <flatbuffers/flatbuffers.h>

#include "rlbot/interface.h"

namespace rlbot {
NamedRenderer::NamedRenderer(std::string name)
    : Renderer((int)std::hash<std::string>()(name)) {}

void NamedRenderer::FinishAndSend() {
  Finish();
  Interface::RenderGroup(flatBufferBuilder.GetBufferPointer(),
                         flatBufferBuilder.GetSize());
}
} // namespace rlbot
