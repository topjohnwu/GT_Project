#include "chromosome.h"
#include "compactGA.h"
#include "pirateGame.h"

int main(int argc, char const *argv[]) {
	PirateGame game;
	// setParams(players, population, precision, resources, generation, simPop)
	game.setParams(3, 1000, 4, 50, 200000, 500);
	game.runGA();
	game.printBit(cout);
	// game.printExpected(cout);
	game.printResult(cout);
	return 0;
}