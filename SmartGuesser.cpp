#include <iostream>
#include <new>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>
#include "SmartGuesser.hpp"

namespace bullpgia
{
////----------------------------------------------------------------------
// Simple log2 function
int SmartGuesser::log2(int num)
{
    int ret = 0;

    while (num /= 2)
        ret++;

    return ret;
}

////----------------------------------------------------------------------
// The utility function for std::sotr() function
bool sort_fun(vector<int> left, vector<int> right)
{
    return (left[1] < right[1]);
}

////----------------------------------------------------------------------
// Creating a guess's number
void SmartGuesser::create_num(char ch, uint left, uint right)
{
    for (uint i = left; i < right; i++)
    {
        if (_right[i] != -1) // will mark 'x' if the digit was founded
        {
            _guess[i] = 'x';
        }
        else
        {
            _guess[i] = ch;
        }
    }
}

////----------------------------------------------------------------------
// Calculate the number of each digit
void SmartGuesser::first_process(int bull)
{
    if (bull > 0)
    {
        _length_step += bull;
        _amount_of_num[_count_step][1] = bull; // store the amount number of each digit

        if (length == _length_step) // will stop when find all digits
        {
            _first_second_process = false; // start the second process

            _count_step = 0;
            sort(_amount_of_num.begin(), _amount_of_num.end(), sort_fun); // sorting to terminate the not uses digits
            while (_amount_of_num[_count_step][1] == 0)                   // moving to the first found number
                _count_step++;

            start_second();
            return;
        }
    }

    _count_step++;
    create_num(char('0' + _count_step), 0, length);
}

////----------------------------------------------------------------------
// For the starting the second process
void SmartGuesser::start_second()
{
    _index = 0;                                  // restart index for new stack of identical digits
    _last_bull = _amount_of_num[_count_step][1]; // for the first step must equal the total amount of the number

    _shift = length;                                                // stor last position of the right-(_r) index
    _l = 0;                                                         // start of the length
    _r = _shift - _shift / 2;                                       // calculate the new position of the right index in the new sublength
    create_num('x', 0, length);                                     // clear the guess
    create_num(char('0' + _amount_of_num[_count_step][0]), _l, _r); // create the guess with new searching digit
}

////----------------------------------------------------------------------
// Calculate the right position of each digit
void SmartGuesser::second_process(int bull)
{
    if (bull > 0)
    {
        if ((_r - _l) == 1) // find the right position
        {
            _right[_l] = char('0' + _amount_of_num[_count_step][0]); // storing the digit in the right position
            _amount_of_num[_count_step][1]--;                        // reducing the number of identical digits

            if (_last_bull == 2) // the special case
            {
                _right[_l + 1] = char('0' + _amount_of_num[_count_step][0]); // storing the digit in the right position
                _amount_of_num[_count_step][1]--;                            // reducing the number of identical digits
            }

            if (_amount_of_num[_count_step][1] == 0) // end of identical digits
            {
                _count_step++;  // nex stack of identical digits
                start_second(); // reload the algorithm (binary search)
            }
            else
            {
                _index--;                          //
                _l = _map_step[_index][0];         //
                _r = _map_step[_index][1];         //
                _last_bull = _map_step[_index][2]; // restore the right frame which contains searching numbers

                _shift = _r;                                                    // stor last position of the right-(_r) index
                _r = _r - ((_r - _l) / 2);                                      // calculate the new position of the right index in the new sublength
                create_num('x', 0, length);                                     // clear the guess
                create_num(char('0' + _amount_of_num[_count_step][0]), _l, _r); // create the guess with new position of the digit
            }
        }
        else
        {
            if (_last_bull - bull) // store the right frame which contains searching numbers
            {
                _map_step[_index][0] = _r;
                _map_step[_index][1] = _shift;
                _map_step[_index][2] = _last_bull - bull;
                _last_bull = bull;
                _index++;
            }

            _shift = _r;                                                    // stor last position of the right-(_r) index
            _r = _r - ((_r - _l) / 2);                                      // calculate the new position of the right index in the new sublength
            create_num('x', 0, length);                                     // clear the guess
            create_num(char('0' + _amount_of_num[_count_step][0]), _l, _r); // create the guess with new position of the digit
        }
    }
    else // bull = 0
    {
        if ((_r - _l) == 1) // find the right position
        {
            _right[_l + 1] = char('0' + _amount_of_num[_count_step][0]); // storing the digit in the right position (_l + 1)!
            _amount_of_num[_count_step][1]--;                            // reducing the number of identical digits

            if (_amount_of_num[_count_step][1] == 0) // end of identical digits
            {
                _count_step++;  // nex stack of identical digits
                start_second(); // reload the algorithm (binary search)
            }
            else
            {
                _index--;                          //
                _l = _map_step[_index][0];         //
                _r = _map_step[_index][1];         //
                _last_bull = _map_step[_index][2]; // restore the right frame which contains searching numbers

                _shift = _r;                                                    // stor last position of the right-(_r) index
                _r = _r - ((_r - _l) / 2);                                      // calculate the new position of the right index in the new sublength
                create_num('x', 0, length);                                     // clear the guess
                create_num(char('0' + _amount_of_num[_count_step][0]), _l, _r); // create the guess with new position of the digit
            }
        }
        else
        {
            _l = _r;                                                        // left index move to the right
            _r = _shift - ((_shift - _r) / 2);                              // calculate the new position of the right index in the new sublength
            create_num('x', 0, length);                                     // clear the guess
            create_num(char('0' + _amount_of_num[_count_step][0]), _l, _r); // create the guess with new position of the digit
        }
    }

    if (_count_step == 9) // the end of second process
    {
        for (uint i = 0; i < length; i++) // add the last stack of identical digits
        {
            if (_right[i] == -1)
                _right[i] = char('0' + _amount_of_num[_count_step][0]);
        }

        _end = true; // the end work of SmartGuesser
    }
}

////----------------------------------------------------------------------
// Preparing the SmartGuesser
void SmartGuesser::startNewGame(uint len)
{
    length = len;

    _end = false;
    _first_second_process = true; // first process
    _count_step = 0;
    _length_step = 0;

    _index = 0;
    _map_step.resize(log2(length) + 2, vector<int>(3));

    _right.resize(length);
    for (uint i = 0; i < length; i++) // will mark that digit is not founded
        _right[i] = -1;

    _guess.resize(length);
    for (uint i = 0; i < length; i++) // always start "0...0"
        _guess[i] = '0';

    _amount_of_num.resize(10, vector<int>(2));
    for (uint i = 0; i < 10; i++)
    {
        _amount_of_num[i][0] = i; // the digit
        _amount_of_num[i][1] = 0; // the amount of digit
    }
}

////----------------------------------------------------------------------
// Returning the guess for each step or right answer in the end
std::string SmartGuesser::guess()
{
    if (_end) // the end work of SmartGuesser
        return string(_right.begin(), _right.end());

    return string(_guess.begin(), _guess.end());
}

////----------------------------------------------------------------------
// Preparing the guessed answer for a next step
void SmartGuesser::learn(string bp)
{
    if (_end) // in this point should already guess
        throw std::logic_error("exception: code bug should already guess");

    int index = bp.find(",");           //
    string token = bp.substr(0, index); //
    int bull = stoi(token);             // convert the bull-string to integer

    if (_first_second_process)
        first_process(bull);
    else
        second_process(bull);
}
} // namespace bullpgia
