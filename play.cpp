/**
 * Implementation of bull-pgia game
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include "play.hpp"
#include "calculate.hpp"
#include <string>
using std::string;

namespace bullpgia
{
size_t play(Chooser &chooser, Guesser &guesser, size_t length, size_t maxTurns)
{
	const size_t TECHNICAL_VICTORY_TO_GUESSER = 0;
	const size_t TECHNICAL_VICTORY_TO_CHOOSER = maxTurns + 1;

	string choice = chooser.choose(length);
	if (choice.length() != length) // Illegal choice
		return TECHNICAL_VICTORY_TO_GUESSER;
	guesser.startNewGame(length); // tell the guesser that a new game starts now
	size_t indexOfTurn;
	for (indexOfTurn = 0; indexOfTurn < maxTurns; ++indexOfTurn)
	{
		string guess = guesser.guess();
		if (guess.length() != length) // Illegal guess
			return TECHNICAL_VICTORY_TO_CHOOSER;
		if (guess == choice)
		{
			return indexOfTurn + 1;
		}
		else
		{
			auto reply = calculateBullAndPgia(choice, guess);
			guesser.learn(reply); // tell the guesser how many bull and pgia were in its latest guess
		}
	}
	return TECHNICAL_VICTORY_TO_CHOOSER; // Guesser could not guess in time
}
} // namespace bullpgia
