#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <thread>

namespace rlbotcpp {
namespace platform {
#ifdef _WIN32
#include "windows.h"

struct ModuleHandle {
  HMODULE platform_specific;
};
#endif

ModuleHandle LoadDll(const char *filename);
void *GetFunctionAddress(ModuleHandle handle, const char *procname);
void FreeDll(ModuleHandle handle);

void SetWorkingDirectory(std::string directory);
std::string GetExecutableDirectory();

void Sleep(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace platform
} // namespace rlbotcpp
