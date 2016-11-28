#ifndef _PIRATE_GAME_
#define _PIRATE_GAME_

#include "compactGA.h"

class PirateGame : public CompactGA {
public:
	PirateGame(int a, int b, int c): CompactGA(a, b, c) {};
private:
	void executeGame();
};

#endif
