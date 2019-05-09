/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "calculate.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

#define RAND_LEN 100 // to increase or decrease the length of the random number (smarty test case)

// simple log2 function
int my_log2(int num)
{
	int ret = 0;

	while (num /= 2)
		ret++;

	return ret;
}

int main()
{
	badkan::TestCase testcase;
	int grade = 0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0)
	{

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
			.CHECK_OUTPUT(calculateBullAndPgia("1234", "1234"), "4,0") // 4 bull, 0 pgia
			.CHECK_OUTPUT(calculateBullAndPgia("1234", "4321"), "0,4") // 0 bull, 4 pgia
			;

		testcase.setname("Play with dummy choosers and guessers")
			.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)	// guesser wins in one turn.
			.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)  // guesser loses by running out of turns
			.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101) // guesser loses technically by making an illegal guess (too long).
			.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)   // chooser loses technically by choosing an illegal number (too long).
			;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		uint bad = 0;
		for (uint i = 0; i < 100; ++i)
		{
			uint num = play(randy, smarty, 4, 100);

			if (num > 100)
				bad++;
		}
		testcase.CHECK_EQUAL((100 - bad) >= 10, true); // smarty should always win in at most 10 turns!

		//
		//
		//-----------------------------------------------------------------------------------
		//
		//

		ConstantChooser _cc{""}, _cc1{"1"}, _cc123{"123"};
		RandomChooser _randy;

		ConstantGuesser _cg{""}, _cg1{"1"}, _cg123{"123"};
		RandomGuesser _rg;
		SmartGuesser _smarty;

		//////
		// 1
		testcase.setname("My test: 1"); //--------------------------------->test 1

		// Constan check equal
		testcase.CHECK_EQUAL(play(_cc, _cg, 0, 100), 1);	   // the special case
		testcase.CHECK_EQUAL(play(_cc1, _cg1, 1, 100), 1);	 // the special case
		testcase.CHECK_EQUAL(play(_cc123, _cg123, 3, 100), 1); // the special case

		// check that doesn't throw an exception
		testcase.CHECK_OK(play(_cc, _cg, 0, 100));		 // the special case
		testcase.CHECK_OK(play(_cc1, _cg1, 1, 100));	 // the special case
		testcase.CHECK_OK(play(_cc123, _cg123, 3, 100)); // the special case

		for (uint i = 0; i < 100; i++) // check that program doesn't throw an exception
		{
			// Random
			testcase.CHECK_OK(play(_randy, _rg, 0, 100)); // the special case
			testcase.CHECK_OK(play(_randy, _rg, 1, 100)); // the special case
			testcase.CHECK_OK(play(_randy, _rg, 3, 100)); // the special case

			// Smart
			testcase.CHECK_OK(play(_randy, _smarty, (rand() % 100), 1000)); // random length

			testcase.CHECK_OK(play(_randy, _smarty, 0, 100)); // the special case
			testcase.CHECK_OK(play(_randy, _smarty, 1, 100)); // the special case
			testcase.CHECK_OK(play(_randy, _smarty, 3, 100)); // the special case
		}

		//////
		// 2
		testcase.setname("My test: 2"); //--------------------------------->test 2

		for (uint i = 0; i < 100; i++) // check the function calculateBullAndPgia()
		{
			int num1 = 1000000 + (rand() % 1000000); //
			int num2 = 1000000 + (rand() % 1000000); // random number 7 digits

			string snum1 = to_string(num1); //
			string snum2 = to_string(num2); // int to string

			uint bull = 0;
			for (uint i = 0; i < snum1.size(); i++)
			{
				if (snum1[i] == snum2[i])
					bull++;
			}

			string expected = std::to_string(bull);			 // creating the result "bull number,pgia number"
			expected += ',';								 // in this case: snum1.size() = snum2.size() = 7
			expected += std::to_string(snum1.size() - bull); // pgia = 7 - bull

			testcase.CHECK_OUTPUT(calculateBullAndPgia(snum1, snum2), expected);
		}

		//////
		// 2
		testcase.setname("My test: 3"); //--------------------------------->test 3

		for (uint i = 0; i < 100; i++) // check that SmartGuesser
		{
			int len = (rand() % RAND_LEN);
			int max_limit = len * my_log2(len) + 15;

			// smarty should always win
			testcase.CHECK_EQUAL(play(_randy, _smarty, len, max_limit) < max_limit, true);
		}

		grade = testcase.grade();
	}
	else
	{
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: " << grade << endl;
	return 0;
}
