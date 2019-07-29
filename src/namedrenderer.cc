#include "namedrenderer.h"

#include "flatbuffers/flatbuffers.h"
#include "interface.h"

NamedRenderer::NamedRenderer(std::string name)
    : Renderer(std::hash<std::string>()(name)) {}

void NamedRenderer::FinishAndSend() {
  Finish();
  Interface::RenderGroup(flatBufferBuilder.GetBufferPointer(),
                         flatBufferBuilder.GetSize());
}
