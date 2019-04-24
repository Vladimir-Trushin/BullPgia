/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
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

	ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
	ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};
	cout << play(c1234, g1234, 4, 100) << "  : "; // prints 1 - guesser wins in one turn.
	cout << "prints 1   - guesser wins in one turn." << endl;
	cout << play(c1234, g9999, 4, 100) << ": "; // prints 101 - guesser loses by running out of turns.
	cout << "prints 101 - guesser loses by running out of turns." << endl;
	cout << play(c1234, g12345, 4, 100) << ": "; // prints 101 - guesser loses technically by making an illegal guess (too long).
	cout << "prints 101 - guesser loses technically by making an illegal guess (too long)." << endl;
	cout << play(c12345, g1234, 4, 100) << "  : "; // prints 0 - chooser loses technically by choosing an illegal number (too long).
	cout << "prints 0   - chooser loses technically by choosing an illegal number (too long)." << endl;

	RandomChooser randy;
	RandomGuesser guessy;
	cout << endl;
	cout << endl;
	cout << "Random guesser";
	size_t bad = 0;
	for (size_t i = 0; i < 100; ++i) // guesser should often win but sometimes lose.
	{
		int num = play(randy, guessy, 2, 100);

		if (i % 10 == 0)
			cout << endl;

		if (-1 < num && num < 10)
			cout << num << "    ";
		else if (10 <= num && num < 100)
			cout << num << "   ";
		else
		{
			bad++;
			cout << "BAD"
				 << "  ";
		}
	}
	cout << endl;
	cout << endl;
	cout << "BAD : " << bad << endl;
	cout << "GOOD: " << (100 - bad) << endl;

	cout << endl;
	cout << endl;

	SmartGuesser smarty;
	cout << "Smart guesser" << endl;
	cout << "Always win. Maximum possible steps for number with length = n = 2^x: O(n*log(n) + 10)" << endl;
	cout << "For this example length = n = 4 and limit 100";
	for (size_t i = 0; i < 100; ++i)
	{
		int num = play(randy, smarty, 4, 100); // smarty should always win in at most 10 turns!

		if (i % 10 == 0)
			cout << endl;

		if (-1 < num && num < 10)
			cout << num << "  ";
		else
			cout << num << " ";
	}

	cout << endl;
	cout << endl;
	cout << "Possible test: Smart guesser" << endl;
	cout << "Possible steps for big random number with length = n: ~ O(n*log(n))" << endl;
	cout << "Maximum possible steps for random number with length = n: O(n*log(n) + 2*n + 10)" << endl;
	cout << "For this example length = random[0, 100] and limit O(n*log(n))" << endl;
	cout << "possible steps: O(n*log(n))" << endl;
	cout << "max steps     : O(n*log(n) + 2*n + 10)" << endl;
	bad = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		int len = (rand() % RAND_LEN);
		int possible = len * my_log2(len);			 // O(n*log(n))
		int max = len * my_log2(len) + 2 * len + 10; // O(n*log(n) + 2*n + 10)
		int num = play(randy, smarty, len, possible);

		if (num > possible)
		{
			bad++;
			cout << "steps: " << num;
			cout << "        \t possible steps: " << possible;
			cout << "        \t max steps: " << max;
			cout << "        \t length: " << len;
			cout << "        \t max - possible  : ";
			cout << (max - possible) << "\t BAD";
		}
		else
		{
			cout << "steps: " << num;
			cout << "        \t possible steps: " << possible;
			cout << "        \t max steps: " << max;
			cout << "        \t length: " << len;
			cout << "        \t possible - steps: " << (possible - num);
		}

		cout << endl;
	};
	cout << endl;
	cout << "BAD : " << bad << endl;
	cout << "GOOD: " << (100 - bad) << endl;

	cout << endl;
	cout << endl;
	cout << "Maximum test: Smart guesser" << endl;
	cout << "Always win" << endl;
	cout << "Maximum possible steps for random number with length = n: O(n*log(n) + 2*n + 10)" << endl;
	cout << "For this example length = random[0, 100] and limit O(n*log(n) + 2*n + 10)" << endl;
	cout << "max steps : O(n*log(n) + 2*n + 10)" << endl;
	bad = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		int len = (rand() % RAND_LEN);
		int max = len * my_log2(len) + 2 * len + 10; // O(n*log(n) + 2*n + 10)
		int num = play(randy, smarty, len, max);

		if (num > max)
		{
			bad++;
			cout << "CAN'T BE!!!" << endl;
		}
		else
		{
			cout << "steps: " << num;
			cout << "        \t max steps: " << max;
			cout << "        \t length: " << len;
			cout << "        \t max - steps: " << (max - num);
		}

		cout << endl;
	};
	cout << endl;
	cout << "BAD : " << bad << endl;
	cout << "GOOD: " << (100 - bad) << endl;

	return 0;
}
