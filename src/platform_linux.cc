#ifdef __linux__

#include "platform.h"

#include <filesystem>
#include <string>

#include <unistd.h>

namespace rlbot {
namespace platform {
ModuleHandle LoadDll(const char *filename) {
  ModuleHandle handle;
  handle.platform_specific = dlopen(filename, RTLD_LAZY);
  return handle;
}

void *GetFunctionAddress(ModuleHandle handle, const char *procname) {
  return dlsym(handle.platform_specific, procname);
}

void FreeDll(ModuleHandle handle) { dlclose(handle.platform_specific); }

void SetWorkingDirectory(std::string directory) { chdir(directory.c_str()); }

std::string GetExecutableDirectory() {
  char filename[1024];
  readlink("/proc/self/exe", filename, sizeof(filename));

  std::filesystem::path path = std::filesystem::path(filename);
  return path.parent_path().generic_string();
}

void SleepMilliseconds(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace platform
} // namespace rlbot
#endif
