#include "rlbot/renderer.h"

#include "rlbot/interface.h"

namespace rlbot {
flatbuffers::Offset<rlbot::flat::Color>
buildColor(flatbuffers::FlatBufferBuilder &builder, Color color) {
  return rlbot::flat::CreateColor(builder, color.a, color.r, color.g, color.b);
}

Renderer::Renderer(int index) : flatBufferBuilder(1000) { _index = index; }

void Renderer::DrawLine3D(Color color, rlbot::flat::Vector3 start,
                          rlbot::flat::Vector3 end) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawLine3D, coloroffset,
      &start, &end));
}

void Renderer::DrawPolyLine3D(
    Color color, std::vector<const rlbot::flat::Vector3 *> points) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  for (int i = 0; i < points.size() - 1; i++) {
    renderMessages.push_back(rlbot::flat::CreateRenderMessage(
        flatBufferBuilder, rlbot::flat::RenderType_DrawLine3D, coloroffset,
        points[i], points[i + 1]));
  }
}

void Renderer::DrawString2D(std::string text, Color color,
                            rlbot::flat::Vector3 upperLeft, int scaleX,
                            int scaleY) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  auto stringoffset = flatBufferBuilder.CreateString(text.c_str());

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawString2D, coloroffset,
      &upperLeft, 0, scaleX, scaleY, stringoffset));
}

void Renderer::DrawString3D(std::string text, Color color,
                            rlbot::flat::Vector3 upperLeft, int scaleX,
                            int scaleY) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  auto stringoffset = flatBufferBuilder.CreateString(text.c_str());

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawString3D, coloroffset,
      &upperLeft, 0, scaleX, scaleY, stringoffset));
}

void Renderer::DrawRect2D(Color color, rlbot::flat::Vector3 upperLeft,
                          int width, int height, bool filled) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawRect2D, coloroffset,
      &upperLeft, 0, width, height, 0, filled));
}
                
void Renderer::DrawRect3D(Color color, rlbot::flat::Vector3 upperLeft,
                          int width, int height, bool filled, bool centered) {
  auto coloroffset = buildColor(flatBufferBuilder, color);

  auto render_type = centered ? rlbot::flat::RenderType_DrawCenteredRect3D
      : rlbot::flat::RenderType_DrawRect3D;

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, render_type, coloroffset,
      &upperLeft, 0, width, height, 0, filled));
}

void Renderer::Clear() { flatBufferBuilder.Clear(); }

void Renderer::Finish() {
  auto messageoffsets = flatBufferBuilder.CreateVector(renderMessages);

  auto groupbuilder = rlbot::flat::RenderGroupBuilder(flatBufferBuilder);
  groupbuilder.add_id(_index);
  groupbuilder.add_renderMessages(messageoffsets);

  auto packet = groupbuilder.Finish();

  flatBufferBuilder.Finish(packet);
}
} // namespace rlbot
