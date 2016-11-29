#include "chromosome.h"
#include "compactGA.h"
#include "pirateGame.h"

int main(int argc, char const *argv[]) {
	PirateGame game;
	game.setParams(3, 10, 8, 10, 5);
	game.runGA();
	game.printCurrent(cout);
	return 0;
}