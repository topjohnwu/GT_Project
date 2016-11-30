#include "chromosome.h"
#include "compactGA.h"
#include "pirateGame.h"

int main(int argc, char const *argv[]) {
	PirateGame game;
	game.setParams(2, 100, 4, 8, 10000, 1000);
	game.runGA();
	game.printExpected(cout);
	return 0;
}