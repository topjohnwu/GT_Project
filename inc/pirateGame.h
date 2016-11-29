#ifndef _PIRATE_GAME_
#define _PIRATE_GAME_

#include "compactGA.h"

class PirateGame : public CompactGA {
protected:
	void executeGame(vector<Chromosome*>&);
};

#endif
