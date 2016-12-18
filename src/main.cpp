#include "chromosome.h"
#include "compactGA.h"
#include "pirateGame.h"

int main(int argc, char const *argv[]) {
	PirateGame game;
	// setParams(int player, int pop, int prec, int res, int gen, int sim)
	game.setParams(3, 100, 4, 8, 100000, 1000);
	game.runGA();
	game.printBit(cout);
	// game.printExpected(cout);
	game.printResult(cout);
	return 0;
}