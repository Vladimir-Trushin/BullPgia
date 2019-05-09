#pragma once

#include <string>

namespace bullpgia
{
class Guesser
{
protected:
  uint length;

public:
  ////----------------------------------------------------------------------
  // Virtual destructor
  virtual ~Guesser();

  ////----------------------------------------------------------------------
  // Stor the length
  virtual void startNewGame(uint len);

  ////----------------------------------------------------------------------
  // Pure virtual function
  virtual std::string guess() = 0;

  ////----------------------------------------------------------------------
  // Do nothing
  virtual void learn(std::string bp);
};
} // namespace bullpgia