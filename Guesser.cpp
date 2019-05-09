#include "Guesser.hpp"

namespace bullpgia
{
////----------------------------------------------------------------------
// Virtual destructor
Guesser::~Guesser()
{
}

////----------------------------------------------------------------------
// Stor the length
void Guesser::startNewGame(uint len)
{
    length = len;
}

////----------------------------------------------------------------------
// Do nothing
void Guesser::learn(std::string bp)
{
    // Do nothing
}

} // namespace bullpgia