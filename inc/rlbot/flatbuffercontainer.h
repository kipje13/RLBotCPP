#pragma once

#include "rlbot/interface.h"

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

  const type *getRoot() const { return flatbuffer; }
  const type *operator->() const { return flatbuffer; }
};
} // namespace rlbot
