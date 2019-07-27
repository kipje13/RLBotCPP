#pragma once

#include <string>

class Platform {
public:
  static void SetWorkingDirectory(std::string directory);
  static std::string GetExecutableDirectory();
};
