#include "compactGA.h"

CompactGA::CompactGA(int players, int population, int precision)
	:_popSize(population), _nPlayers(players), _genePrecision(precision)
{
	_probVec.resize(_nPlayers);
	for(int i = 0; i < _nPlayers; ++i) {
		_probVec[i].resize(_popSize);
		for(int j = 0; j < _popSize; ++j) {
			_probVec[i][j] = 0.5;
		}
	}
	_populations.resize(_nPlayers);
	for(int i = 0; i < _nPlayers; ++i) {
		_populations[i].resize(_popSize);
		for(int j = 0; j < _popSize; ++j) {
			_populations[i][j].init(i, precision, _nPlayers);
		}
	}
	_results.resize(_nPlayers);
	for(int i = 0; i < _nPlayers; ++i) {
		_results[i].resize(_popSize);
	}
}
