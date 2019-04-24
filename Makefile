#!make -f

all: test
	./$<

demo:  Demo.o DummyChoosers.o DummyGuessers.o play.o calculate.o Guesser.o SmartGuesser.o
	clang++-5.0 -std=c++17 $^ -o demo

test:  Test.o DummyChoosers.o DummyGuessers.o play.o calculate.o Guesser.o SmartGuesser.o
	clang++-5.0 -std=c++17 $^ -o test

Demo.o: Demo.cpp play.hpp DummyChoosers.hpp DummyGuessers.hpp SmartGuesser.hpp
	clang++-5.0 -std=c++17 --compile Demo.cpp -o Demo.o

Guesser.o: Guesser.cpp Guesser.hpp
	clang++-5.0 -std=c++17 --compile Guesser.cpp -o Guesser.o

Test.o: Test.cpp play.hpp calculate.hpp Chooser.hpp DummyChoosers.hpp Guesser.hpp DummyGuessers.hpp badkan.hpp
	clang++-5.0 -std=c++17 --compile Test.cpp -o Test.o

play.o: play.cpp play.hpp calculate.hpp
	clang++-5.0 -std=c++17 --compile play.cpp -o play.o

calculate.o: calculate.cpp calculate.hpp
	clang++-5.0 -std=c++17 --compile calculate.cpp -o calculate.o

DummyChoosers.o: DummyChoosers.cpp DummyChoosers.hpp
	clang++-5.0 -std=c++17 --compile DummyChoosers.cpp -o DummyChoosers.o

DummyGuessers.o: DummyGuessers.cpp DummyGuessers.hpp
	clang++-5.0 -std=c++17 --compile DummyGuessers.cpp -o DummyGuessers.o

#SmartGuesser.o:  SmartGuesser.cpp SmartGuesser.hpp
#	clang++-5.0 -std=c++17 --compile SmartGuesser.cpp -o SmartGuesser.o

clean:
	rm -f DummyGuessers.o DummyChoosers.o calculate.o play.o Test.o Guesser.o Demo.o demo test
