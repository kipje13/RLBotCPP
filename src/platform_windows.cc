#ifdef _WIN32

#include "platform.h"

#include <filesystem>
#include <string>

#include <direct.h>
#include <windows.h>

namespace rlbotcpp {
namespace platform {
ModuleHandle LoadDll(const char *filename) {
  ModuleHandle handle;
  handle.platform_specific = LoadLibrary(filename);
  return handle;
}

void *GetFunctionAddress(ModuleHandle handle, const char *procname) {
  return GetProcAddress(handle.platform_specific, procname);
}

void FreeDll(ModuleHandle handle) { FreeLibrary(handle.platform_specific); }

void SetWorkingDirectory(std::string directory) { _chdir(directory.c_str()); }

std::string GetExecutableDirectory() {
  char filename[1024];
  GetModuleFileName(NULL, filename, sizeof(filename));

  std::filesystem::path path = std::filesystem::path(filename);
  return path.parent_path().generic_string();
}
} // namespace platform
} // namespace rlbotcpp
#endif
