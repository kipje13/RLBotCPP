#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <thread>

namespace rlbot {
namespace platform {
#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>

struct ModuleHandle {
  HMODULE platform_specific;
};

const char fileSeperator = '\\';
#endif

#ifdef __linux__
#include <dlfcn.h>

struct ModuleHandle {
  void *platform_specific;
};

const char fileSeperator = '/';
#endif

ModuleHandle LoadDll(const char *filename);
void *GetFunctionAddress(ModuleHandle handle, const char *procname);
void FreeDll(ModuleHandle handle);

void SetWorkingDirectory(std::string directory);
std::string GetExecutableDirectory();

void SleepMilliseconds(uint32_t ms);
} // namespace platform
} // namespace rlbot
