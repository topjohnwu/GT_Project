#include "CompactGA.h"
#include "pirateGame.h"

void PirateGame::executeGame(vector<Chromosome*>& players) {
	for(unsigned i = 0; i < _nPlayers; ++i) {
		vector<int> distribution;
		distribution.reserve(_nPlayers);

		//1 player left case
		if(i == _nPlayers - 1) {
			players[i]->_gameResult = _nResources;
			break;
		}

		//get distribution
		players[i]->distribute(_nResources, _maxPrec, distribution);

		//vote
		int nCount = 0;
		int pCount = 1; // 1 for self vote
		for(unsigned j = i + 1; j < _nPlayers; ++j) {
			if(players[j]->vote(_maxPrec, distribution)) ++pCount;
			else ++ nCount;
		}

		//result
		if(pCount >= nCount) {
			for(unsigned j = i; j < _nPlayers; ++j) {
				players[j]->_gameResult = distribution[j];
			}
			break;
		}
		else players[i]->_gameResult = -1; //eliminated
	}
}
