#include "compactGA.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

void CompactGA::setParams(int player, int pop, int pre, int res, int gen, int sim) {
	setPlayerNumber(player);
	setPopSize(pop);
	setPrecision(pre);
	setResNum(res);
	setGeneration(gen);
	setSimPopSize(sim);
}

void CompactGA::init() {
	_populations.resize(_nPlayers);
	_probVec.resize(_nPlayers);
	for(int i = 0; i < _nPlayers; ++i) {
		_populations[i].resize(_popSize);
		for(int j = 0; j < _popSize; ++j) {
			_populations[i][j].init(_nPlayers - i, _genePrecision, _nPlayers, _nResources);
		}
		// _probVec[i].resize(2 * _nPlayers - i);
		_probVec[i].resize(_nPlayers - i);
		for(int j = 0, size = _probVec[i].size(); j < size; ++j) {
			_probVec[i][j].resize(_genePrecision, 0.5);
		}
	}
	// _probVec[0][0][0] = 0;
	// _probVec[0][0][1] = 1;
	// _probVec[0][0][2] = 1;
	// _probVec[0][0][3] = 1;
	// _probVec[0][1][0] = 0;
	// _probVec[0][1][1] = 0;
	// _probVec[0][1][2] = 0;
	// _probVec[0][1][3] = 0;
	// _probVec[1][1][0] = 1;
	// _probVec[1][1][1] = 1;
	// _probVec[1][1][2] = 1;
	// _probVec[1][1][3] = 1;
	// _probVec[2][0][0] = 1;
	// _probVec[2][0][1] = 1;
	// _probVec[2][0][2] = 1;
	// _probVec[2][0][3] = 1;
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
	_maxPrec = pow(2, pre) - 1;
}

void CompactGA::setResNum(int res) {
	_nResources = res;
}

void CompactGA::setGeneration(int gen) {
	_nGeneration = gen;
}

void CompactGA::setSimPopSize(int sim) {
	_simPopSize = sim;
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
				//ignore convergence of vote stategy of top-ordered player
				if(i == 0 && j >= _nPlayers - 1) continue;
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
		generate();
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
				if(_populations[i][j]._gameResult == _populations[i][j+1]._gameResult)
					continue;
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
								_probVec[i][x][y] += 1.0 / _simPopSize;
								if(_probVec[i][x][y] > 1.0) _probVec[i][x][y] = 1.0;
							} else {
								_probVec[i][x][y] -= 1.0 / _simPopSize;
								if(_probVec[i][x][y] < 0.0) _probVec[i][x][y] = 0.0;
							}
							if(_probVec[i][x][y] < 1.0 / _simPopSize) 
								_probVec[i][x][y] = 0.0;
						}
					}
				}
			}
		}
		// printCurrent(cout);
	}
}

void CompactGA::printResult(ostream& out) {
	out << "total resources: " << _nResources << '\n';
	for(int i = 0, s1 = _probVec.size(); i < s1; ++i) {
		int tempRes = _nResources;
		vector<double> genes;
		genes.reserve(_nPlayers - i);
		// convert result bits to double
		for(int j = 0, s2 = _probVec[i].size(); j < s2; ++j) {
			double temp = 0;
			for(int k = 0, s3 = _probVec[i][j].size(); k < s3; ++k) {
				temp *= 2;
				temp += _probVec[i][j][k];
			}
			genes.push_back(temp);
		}

		out << "Player" << i+1 << ":\n";
		out << "distribute: ";

		// convert result to distribution
		for(unsigned j = 0; j < i; ++j) {
			out << "* ";
		}
		for(unsigned j = 0; j < _nPlayers-i-1; ++j) {
			int temp = (double)tempRes * genes[j] / (double)_maxPrec + 0.5;
			out << temp << ' ';
			tempRes -= temp;
		}
		out << tempRes << ' ';
		out << "\nthreshold: ";
		if(i == 0) out << "*\n";
		else out << genes.back() / (double)_maxPrec << '\n';
	}
	out.flush();
}

void CompactGA::printExpected(ostream& out) {
	for(int i = 0, s1 = _probVec.size(); i < s1; ++i) {
		for(int j = 0, s2 = _probVec[i].size(); j < s2; ++j) {
			double temp = 0;
			for(int k = 0, s3 = _probVec[i][j].size(); k < s3; ++k) {
				temp *= 2;
				temp += _probVec[i][j][k];
				// out << setprecision(3) << _probVec[i][j][k] << " ";
			}
			out << setprecision(3) << (double)temp / (double)_maxPrec << ' ';
		}
		out << "\n";
	}
	out.flush();
}

void CompactGA::printBit(ostream& out) {
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
