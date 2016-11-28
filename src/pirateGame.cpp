#include "CompactGA.h"
#include "pirateGame.h"

void PirateGame::executeGame() {
	vector<int> distribution;
	distribution.resize(_popSize);
	for(int i = 0; i < _nPlayers; ++i) {
		for(unsigned j = 0; j < _popSize; ++j) {
			//1 player left case
			if(j == _popSize - 1) {
				_results[i][j] = _nResources;
				break;
			}

			//get distribution
			_populations[i][j].distribute(_nResources, _maxPrec, distribution);

			//vote
			int nCount = 0;
			int pCount = 1; // 1 for self vote
			for(unsigned k = j + 1; k < _popSize; ++k) {
				if(_populations[i][k].vote(_maxPrec, distribution)) ++pCount;
				else ++ nCount;
			}

			//result
			if(pCount >= nCount) {
				for(unsigned k = j; k < _popSize; ++k) {
					_results[i][k] = distribution[k];
				}
				break;
			}
			else _results[i][j] = -1; //eliminated
		}
	}
}
