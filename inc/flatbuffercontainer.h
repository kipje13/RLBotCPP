#pragma once

#include "interface.h"

#include <cstdlib>

namespace rlbot {
template <typename type> class FlatbufferContainer {
private:
  char *data;
  size_t size;
  const type *flatbuffer;

public:
  FlatbufferContainer(ByteBuffer buffer) {
    size = buffer.size;
    data = (char *)malloc(size);
    memcpy(data, buffer.ptr, size);

    flatbuffer = flatbuffers::GetRoot<type>(data);
  }

  ~FlatbufferContainer() { free(data); }

  FlatbufferContainer(const FlatbufferContainer &flatbuffercontainer) {
    size = flatbuffercontainer.size;
    data = (char *)malloc(size);
    memcpy(data, flatbuffercontainer.data, size);

    flatbuffer = flatbuffers::GetRoot<type>(data);
  }

  FlatbufferContainer(FlatbufferContainer &&flatbuffercontainer) {
    size = flatbuffercontainer.size;
    data = flatbuffercontainer.data;

    flatbuffer = flatbuffers::GetRoot<type>(data);

    flatbuffercontainer.data = nullptr;
    flatbuffercontainer.size = 0;
  }

  FlatbufferContainer<type>
  operator=(const FlatbufferContainer &flatbuffercontainer) {
    size = flatbuffercontainer.size;
    data = (char *)malloc(size);
    memcpy(data, flatbuffercontainer.data, size);

    flatbuffer = flatbuffers::GetRoot<type>(data);
  }

  FlatbufferContainer<type>
  operator=(FlatbufferContainer &&flatbuffercontainer) {
    size = flatbuffercontainer.size;
    data = flatbuffercontainer.data;

    flatbuffer = flatbuffers::GetRoot<type>(data);

    flatbuffercontainer.data = nullptr;
    flatbuffercontainer.size = 0;
  }

  const type *operator->() const { return flatbuffer; }
};

typedef FlatbufferContainer<rlbot::flat::GameTickPacket> GameTickPacket;
typedef FlatbufferContainer<rlbot::flat::BallPrediction> BallPrediction;
typedef FlatbufferContainer<rlbot::flat::FieldInfo> FieldInfo;
typedef FlatbufferContainer<rlbot::flat::FieldInfo> MatchInfo;
} // namespace rlbot
