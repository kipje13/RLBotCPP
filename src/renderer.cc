#include "renderer.h"

#include "interface.h"

Renderer::Renderer(int index) { _index = index; }

void Renderer::DrawLine3D(Color color, rlbot::flat::Vector3 start,
                          rlbot::flat::Vector3 end) {
  auto colorbuilder = rlbot::flat::ColorBuilder(flatBufferBuilder);
  colorbuilder.add_a(color.a);
  colorbuilder.add_r(color.r);
  colorbuilder.add_g(color.g);
  colorbuilder.add_b(color.b);
  auto coloroffset = colorbuilder.Finish();

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawLine3D, coloroffset,
      &start, &end));
}

void Renderer::DrawPolyLine3D(Color color,
                              std::vector<const rlbot::flat::Vector3*> points) {
  auto colorbuilder = rlbot::flat::ColorBuilder(flatBufferBuilder);
  colorbuilder.add_a(color.a);
  colorbuilder.add_r(color.r);
  colorbuilder.add_g(color.g);
  colorbuilder.add_b(color.b);
  auto coloroffset = colorbuilder.Finish();

  for (int i = 0; i < points.size() - 1; i++) {
    renderMessages.push_back(rlbot::flat::CreateRenderMessage(
        flatBufferBuilder, rlbot::flat::RenderType_DrawLine3D, coloroffset,
        points[i], points[i + 1]));
  }
}

void Renderer::DrawString2D(std::string text, Color color,
                            rlbot::flat::Vector3 upperLeft, int scaleX,
                            int scaleY) {
  auto colorbuilder = rlbot::flat::ColorBuilder(flatBufferBuilder);
  colorbuilder.add_a(color.a);
  colorbuilder.add_r(color.r);
  colorbuilder.add_g(color.g);
  colorbuilder.add_b(color.b);
  auto coloroffset = colorbuilder.Finish();

  auto stringoffset = flatBufferBuilder.CreateString(text.c_str());

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawString2D, coloroffset,
      &upperLeft, 0, scaleX, scaleY, stringoffset));
}

void Renderer::DrawString3D(std::string text, Color color,
                            rlbot::flat::Vector3 upperLeft, int scaleX,
                            int scaleY) {
  auto colorbuilder = rlbot::flat::ColorBuilder(flatBufferBuilder);
  colorbuilder.add_a(color.a);
  colorbuilder.add_r(color.r);
  colorbuilder.add_g(color.g);
  colorbuilder.add_b(color.b);
  auto coloroffset = colorbuilder.Finish();

  auto stringoffset = flatBufferBuilder.CreateString(text.c_str());

  renderMessages.push_back(rlbot::flat::CreateRenderMessage(
      flatBufferBuilder, rlbot::flat::RenderType_DrawString3D, coloroffset,
      &upperLeft, 0, scaleX, scaleY, stringoffset));
}

void Renderer::Finish() {
  auto messageoffsets = flatBufferBuilder.CreateVector(renderMessages);

  auto groupbuilder = rlbot::flat::RenderGroupBuilder(flatBufferBuilder);
  groupbuilder.add_id(0);
  groupbuilder.add_renderMessages(messageoffsets);

  auto packet = groupbuilder.Finish();

  flatBufferBuilder.Finish(packet);
}
