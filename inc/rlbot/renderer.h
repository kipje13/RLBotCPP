#pragma once

#include <flatbuffers/flatbuffers.h>

#include "rlbot/rlbot_generated.h"
#include "rlbot/color.h"

#include <vector>

namespace rlbot {
class Renderer {
private:
  int _index;
  std::vector<flatbuffers::Offset<rlbot::flat::RenderMessage>> renderMessages;

public:
  void DrawLine3D(Color color, rlbot::flat::Vector3 start,
                  rlbot::flat::Vector3 end);
  void DrawPolyLine3D(Color color,
                      std::vector<const rlbot::flat::Vector3 *> points);
  void DrawString2D(std::string text, Color color,
                    rlbot::flat::Vector3 upperLeft, int scaleX, int scaleY);
  void DrawString3D(std::string text, Color color,
                    rlbot::flat::Vector3 upperLeft, int scaleX, int scaleY);
  void DrawRect2D(Color color, rlbot::flat::Vector3 upperLeft,
                  int width, int height, bool filled);
  void DrawRect3D(Color color, rlbot::flat::Vector3 upperLeft,
                  int width, int height, bool filled, bool centered = false);
  void Clear();

protected:
  Renderer(int index);
  flatbuffers::FlatBufferBuilder flatBufferBuilder;
  void Finish();
};
} // namespace rlbot
