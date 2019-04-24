#include <string>
#include "calculate.hpp"

////----------------------------------------------------------------------
// Check the matching the digits
string calculateBullAndPgia(string choice, string guess)
{
    std::string ret = "";
    size_t bull = 0;

    for (size_t i = 0; i < choice.size(); i++)
    {
        if (choice[i] == guess[i])
            bull++;
    }

    ret = std::to_string(bull);
    ret += ',';
    ret += std::to_string(choice.size() - bull);

    return ret;
}
