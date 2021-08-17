#pragma once

#include "rlbot/rlbot.h"

#include <chrono>
#include <string>
#include <thread>

#ifdef OS_WINDOWS
#include <windows.h>
#endif

#ifdef OS_UNIX
#include <dlfcn.h>
#endif

namespace rlbot {
namespace platform {

#ifdef OS_WINDOWS
struct ModuleHandle {
  HMODULE platform_specific;
};

const char fileSeperator = '\\';
template <typename T>
T GetFunctionAddress(ModuleHandle handle, const char *procname) {
  return (T) GetProcAddress(handle.platform_specific, procname);
}

#endif

#ifdef OS_UNIX
struct ModuleHandle {
  void *platform_specific;
};

const char fileSeperator = '/';
template <typename T>
T GetFunctionAddress(ModuleHandle handle, const char *procname) {
  return (T) dlsym(handle.platform_specific, procname);
}
#endif

ModuleHandle LoadDll(const char *filename);
void FreeDll(ModuleHandle handle);

void SetWorkingDirectory(std::string directory);
std::string GetExecutableDirectory();

void SleepMilliseconds(uint32_t ms);
} // namespace platform
} // namespace rlbot
