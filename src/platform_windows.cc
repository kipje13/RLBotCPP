#ifdef _WIN32

#include "platform.h"

#include <filesystem>
#include <string>

#include <direct.h>
#include <windows.h>

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
