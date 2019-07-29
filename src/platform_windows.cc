#ifdef _WIN32

#include "platform.h"

#include <filesystem>
#include <string>

#include <direct.h>
#include <windows.h>

ModuleHandle Platform::LoadDll(const char *filename) {
  ModuleHandle handle;
  handle.platform_specific = LoadLibrary(filename);
  return handle;
}

void *Platform::GetFunctionAddress(ModuleHandle handle, const char *procname) {
  return GetProcAddress(handle.platform_specific, procname);
}

void Platform::FreeDll(ModuleHandle handle) {
  FreeLibrary(handle.platform_specific);
}

void Platform::SetWorkingDirectory(std::string directory) {
  _chdir(directory.c_str());
}

std::string Platform::GetExecutableDirectory() {
  char filename[1024];
  GetModuleFileName(NULL, filename, sizeof(filename));

  std::filesystem::path path = std::filesystem::path(filename);
  return path.parent_path().generic_string();
}
#endif
