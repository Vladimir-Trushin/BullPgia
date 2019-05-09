#pragma once

#include <string>

namespace bullpgia
{
class Chooser
{
public:
  ////----------------------------------------------------------------------
  // Virtual destructor
  virtual ~Chooser(){};

  ////----------------------------------------------------------------------
  // Pure virtual function
  virtual std::string choose(uint len) = 0;
};
} // namespace bullpgia
