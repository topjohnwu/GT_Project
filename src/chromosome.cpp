#include "chromosome.h"

Chromosome::Chromosome(int order, int prec, int nPlayer): 
		_order(order), _precision(prec), _nPlayers(nPlayer) 
{
	_nGene = order+nPlayer; // order-1 + nPlayer+1
	_genes.resize(_nGene);
	for(unsigned i = 0; i < _genes.size(); ++i) {
		_genes[i].resize(_precision);
	}
}

void Chromosome::geneDecode(vector<int>& res) {
	for(unsigned i = 0; i < _nGene; ++i) {
		int temp = 0;
		for(unsigned j = 0; j < _precision; ++j) {
			temp *= 2;
			temp += _genes[i][j];
		}
		res.push_back(temp);
	}
}

void Chromosome::distribute(int nRes, int maxPrec, vector<int>& distr) {
	int tempRes = nRes;
	vector<int> genes;
	geneDecode(genes);
	for(unsigned j = 0; j < _nPlayers - _order; ++j) {
		distr.push_back(0);
	}
	for(unsigned j = 0; j < _order-1; ++j) {
		int temp = (double)tempRes*(double)genes[j]/(double)maxPrec+0.5;
		distr.push_back(temp);
		tempRes -= temp;
	}
	distr.push_back(tempRes);
}

bool Chromosome::vote(int maxPrec, const vector<int>& distr) {
	vector<int> genes;
	geneDecode(genes);
	double value = 0;
	double threshold = genes.back();
	for(unsigned i = 0; i < _nPlayers; ++i) {
		value += (double)genes[i+_order-1] * (double)distr[i] / (double)maxPrec;
	}
	if(value >= threshold) return true;
	return false;
}