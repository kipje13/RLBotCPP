#pragma once

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

#include <stdint.h>

#include <vector>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

class Renderer {
 private:
  int _index;
  std::vector<flatbuffers::Offset<rlbot::flat::RenderMessage>> renderMessages;

 public:
  void DrawLine3D(Color color, rlbot::flat::Vector3 start,
                  rlbot::flat::Vector3 end);
  void DrawPolyLine3D(Color color,
                      std::vector<const rlbot::flat::Vector3*> vectors);
  void DrawString2D(std::string text, Color color,
                    rlbot::flat::Vector3 upperLeft, int scaleX, int scaleY);
  void DrawString3D(std::string text, Color color,
                    rlbot::flat::Vector3 upperLeft, int scaleX, int scaleY);

 protected:
  Renderer(int index);
  flatbuffers::FlatBufferBuilder flatBufferBuilder;
  void Finish();
};
