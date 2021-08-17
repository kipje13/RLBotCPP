#include "rlbot/platform.h"

#ifdef OS_WINDOWS

#include <filesystem>
#include <string>

#include <direct.h>
#include <windows.h>

namespace rlbot {
namespace platform {
ModuleHandle LoadDll(const char *filename) {
  ModuleHandle handle;
  handle.platform_specific = LoadLibrary(filename);
  return handle;
}

void FreeDll(ModuleHandle handle) { FreeLibrary(handle.platform_specific); }

void SetWorkingDirectory(std::string directory) { _chdir(directory.c_str()); }

std::string GetExecutableDirectory() {
  char filename[1024];
  GetModuleFileName(NULL, filename, sizeof(filename));

  std::filesystem::path path = std::filesystem::path(filename);
  return path.parent_path().generic_string();
}

void SleepMilliseconds(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace platform
} // namespace rlbot
#endif
