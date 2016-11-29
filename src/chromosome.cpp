#include "chromosome.h"
#include <random>

void Chromosome::init(int order, int prec, int nPlayer) {
	_order = order;
	_precision = prec;
	_nPlayers = nPlayer;
	_nGene = order + nPlayer; // order-1 + nPlayer+1
	_genes.resize(_nGene);
	for(unsigned i = 0; i < _nGene; ++i) {
		_genes[i].resize(_precision);
	}
}

vector<int> Chromosome::geneDecode() {
	vector<int> ret;
	for(unsigned i = 0; i < _nGene; ++i) {
		int temp = 0;
		for(unsigned j = 0; j < _precision; ++j) {
			temp *= 2;
			temp += _genes[i][j];
		}
		ret.push_back(temp);
	}
	return ret;
}

void Chromosome::distribute(int nRes, int maxPrec, vector<int>& distr) {
	int tempRes = nRes;
	vector<int> genes = geneDecode();
	for(unsigned i = 0; i < _nPlayers - _order; ++i) {
		distr[i] = 0;
	}
	for(unsigned i = 0; i < _order - 1; ++i) {
		int temp = (double)tempRes*(double)genes[i]/(double)maxPrec+0.5;
		distr[i] = temp;
		tempRes -= temp;
	}
	distr[_nPlayers - 1] = tempRes;
}

bool Chromosome::vote(int maxPrec, const vector<int>& distr) {
	vector<int> genes = geneDecode();
	double value = 0;
	double threshold = genes.back();
	for(unsigned i = 0; i < _nPlayers; ++i) {
		value += (double)genes[i+_order-1] * (double)distr[i] / (double)maxPrec;
	}
	if(value >= threshold) return true;
	return false;
}

void Chromosome::setGenes(const vector< vector<double> >& probVec) {
	uniform_real_distribution<double> uniRand(0.0, 1.0);
	default_random_engine generator;
	for(int i = 0; i < _nGene; ++i) {
		for(int j = 0; j < _precision; ++j) {
			_genes[i][j] = (probVec[i][j] > uniRand(generator)) ? 1 : 0;
		}
	}
}