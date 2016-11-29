#include "compactGA.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

void CompactGA::setParams(int player, int pop, int pre, int res, int gen) {
	setPlayerNumber(player);
	setPopSize(pop);
	setPrecision(pre);
	setResNum(res);
	setGeneration(gen);
}

void CompactGA::init() {
	_populations.resize(_nPlayers);
	_probVec.resize(_nPlayers);
	for(int i = 0; i < _nPlayers; ++i) {
		_populations[i].resize(_popSize);
		for(int j = 0; j < _popSize; ++j) {
			_populations[i][j].init(_nPlayers - i, _genePrecision, _nPlayers);
		}
		_probVec[i].resize(2 * _nPlayers - i);
		for(int j = 0, size = _probVec[i].size(); j < size; ++j) {
			_probVec[i][j].resize(_genePrecision, 0.5);
		}
	}
}

void CompactGA::setPlayerNumber(int num) {
	_nPlayers = num;
}

void CompactGA::setPopSize(int pop) {
	assert(!(pop % 2));
	_popSize = pop;
}

void CompactGA::setPrecision(int pre) {
	_genePrecision = pre;
	_maxPrec = pow(2, pre);
}

void CompactGA::setResNum(int res) {
	_nResources = res;
}

void CompactGA::setGeneration(int gen) {
	_nGeneration = gen;
}

void CompactGA::generate() {
	for(unsigned i = 0; i < _nPlayers; ++i) {
		for(unsigned j = 0; j < _popSize; ++j) {
			_populations[i][j].setGenes(_probVec[i]);
		}
	}
}

bool CompactGA::checkTermCond() {
	for(int i = 0, s1 = _probVec.size(); i < s1; ++i) {
		for(int j = 0, s2 = _probVec[i].size(); j < s2; ++j) {
			for(int k = 0, s3 = _probVec[i][j].size(); k < s3; ++k) {
				if((_probVec[i][j][k] != 0.0) && (_probVec[i][j][k] != 1.0))
					return false;
			}
		}
	}
	return true;
}

void CompactGA::runGA() {
	init();
	for(unsigned u = 0; u < _nGeneration; ++u) {
		if(checkTermCond()) break;
		for(unsigned j = 0; j < _popSize; ++j) {
			vector<Chromosome*> players;
			for(unsigned k = 0; k < _nPlayers; ++k) {
				players.push_back(&_populations[k][j]);
			}
			executeGame(players);
		}
		Chromosome *winner, *loser;
		for(unsigned i = 0; i < _nPlayers; ++i) {
			for(unsigned j = 0; j < _popSize; j += 2) {
				if(_populations[i][j]._gameResult > _populations[i][j+1]._gameResult) {
					winner = &_populations[i][j];
					loser = &_populations[i][j+1];
				} else {
					winner = &_populations[i][j+1];
					loser = &_populations[i][j];
				}
				for(unsigned x = 0; x < winner->_nGene; ++x) {
					for(unsigned y = 0; y < _genePrecision; ++y) {
						if(winner->_genes[x][y] != loser->_genes[x][y]) {
							if(winner->_genes[x][y] == 1) {
								_probVec[i][x][y] += 1.0 / _popSize;
								if(_probVec[i][x][y] > 1.0) _probVec[i][x][y] = 1.0;
							} else {
								_probVec[i][x][y] -= 1.0 / _popSize;
								if(_probVec[i][x][y] < 0.0) _probVec[i][x][y] = 0.0;
							}
						}
					}
				}
			}
		}
	}
}

void CompactGA::printCurrent(ostream& out) {
	for(int i = 0, s1 = _probVec.size(); i < s1; ++i) {
		for(int j = 0, s2 = _probVec[i].size(); j < s2; ++j) {
			for(int k = 0, s3 = _probVec[i][j].size(); k < s3; ++k) {
				out << setprecision(3) << _probVec[i][j][k] << " ";
			}
			out << "\n";
		}
		out << "\n";
	}
	out.flush();
}
