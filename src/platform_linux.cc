#include "rlbot/platform.h"

#ifdef OS_UNIX

#include <string>

#include <libgen.h>
#include <unistd.h>

namespace rlbot {
namespace platform {
ModuleHandle LoadDll(const char *filename) {
  ModuleHandle handle;
  handle.platform_specific = dlopen(filename, RTLD_NOW);
  return handle;
}

void FreeDll(ModuleHandle handle) { dlclose(handle.platform_specific); }

void SetWorkingDirectory(std::string directory) { chdir(directory.c_str()); }

std::string GetExecutableDirectory() {
  char filename[1024];
  readlink("/proc/self/exe", filename, sizeof(filename));

  char *dir = dirname(filename);
  return std::string(dir);
}

void SleepMilliseconds(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace platform
} // namespace rlbot
#endif
