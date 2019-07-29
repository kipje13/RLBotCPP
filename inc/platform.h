#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <thread>

#ifdef _WIN32
#include "windows.h"

struct ModuleHandle {
  HMODULE platform_specific;
};
#endif

class Platform {
public:
  static ModuleHandle LoadDll(const char *filename);
  static void *GetFunctionAddress(ModuleHandle handle, const char *procname);
  static void FreeDll(ModuleHandle handle);

  static void SetWorkingDirectory(std::string directory);
  static std::string GetExecutableDirectory();

  static void Sleep(uint32_t ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }
};
