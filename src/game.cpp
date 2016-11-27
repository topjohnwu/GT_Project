#include <vector>
#include "CompactGA.h"

void CompactGA::executeGame(vector<Chromosome>& players) {
	vector<int> distribution;
	distribution.reserve(players.size());
	for(unsigned i = 0; i < players.size(); ++i) {
		//1 player left case
		if(i == players.size()-1) {
			players[i]._gameResult = _nResources;
			break;
		}

		//get distribution
		distribution.clear();
		players[i].distribute(_nResources, _maxPrec, distribution);

		//vote
		int nCount = 0;
		int pCount = 1; // 1 for self vote
		for(unsigned j = i+1; j < players.size(); ++j) {
			if(players[j].vote(_maxPrec, distribution)) ++pCount;
			else ++ nCount;
		}

		//result
		if(pCount >= nCount) {
			for(unsigned j = i; j < players.size(); ++j) {
				players[j]._gameResult = distribution[j];
			}
			break;
		}
		else players[i]._gameResult = -1; //eliminated
	}
}