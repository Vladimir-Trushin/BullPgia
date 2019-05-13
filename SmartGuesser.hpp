#pragma once

//=================================================================
// The class SmartGuesser is part of the game bullpgia.
//
// The class SmartGuesser provide the algorithm which
// calculates a number with maximum steps:
// 1) if length of number is n = 2^x    : n*log(n) + 10
// 2) if length of number is n = random : n*log(n) + 15
//
// The algorithm based on binary search
//

#include <vector>
#include "Guesser.hpp"

using std::string;
using std::vector;

namespace bullpgia
{
class SmartGuesser : public bullpgia::Guesser
{
private:
  vector<char> _right;                // store right answer
  vector<char> _guess;                // for calculating each digit of the number
  vector<vector<int>> _amount_of_num; // store amount of each digit of the number (need for the first process)
  vector<vector<int>> _map_step;      // contains the right frames which searching numbers
  bool _first_second_process;         // indicating which process now (first = true, second = false)
  bool _end;                          // notification that number calculated (the end work of SmartGuesser)
  int _index;                         // index of _map_step
  int _last_bull;                     // contains the last bull
  int _count_step;                    // counter for _amount_of_num
  int _length_step;                   // number of all amount of digit (at the end of the first process equals the length)
  int _shift;                         // last position of the right-(_r) index (need for the second process)
  int _l;                             // left index (need for the second process)
  int _r;                             // right index (need for the second process)

  ////----------------------------------------------------------------------
  // Creating random numbers [0-9]
  vector<int> random_num();

  ////----------------------------------------------------------------------
  // Creating a guess's number
  void create_num(char ch, uint left, uint right);

  ////----------------------------------------------------------------------
  // Calculate the number of each digit
  void first_process(int bull);

  ////----------------------------------------------------------------------
  // For the starting the second process
  void start_second();

  ////----------------------------------------------------------------------
  // Calculate the right position of each digit
  void second_process(int bull);

  //
  //---------------------------INTERFACE------------------------------------
  //

public:
  ////----------------------------------------------------------------------
  // Simple log2 function
  static int log2(int num);

  ////----------------------------------------------------------------------
  // Preparing the SmartGuesser
  void startNewGame(uint len) override;

  ////----------------------------------------------------------------------
  // Returning the guess for each step or right answer in the end
  string guess() override;

  ////----------------------------------------------------------------------
  // Preparing the guessed answer for a next step
  void learn(string bp) override;
};
} // namespace bullpgia
