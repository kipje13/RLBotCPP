#include "scopedrenderer.h"

ScopedRenderer::ScopedRenderer(std::string name) : NamedRenderer(name) {}

ScopedRenderer::~ScopedRenderer() { FinishAndSend(); }
