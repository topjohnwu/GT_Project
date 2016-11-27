#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>

using namespace std;

class Chromosome
{
	friend class CompactGA;

	Chromosome(int order, int prec, int nPlayer): 
		_order(order), _precision(prec), _nPlayers(nPlayer)
	{
		_nGene = order+nPlayer; // order-1 + nPlayer+1
		_genes.resize(_nGene);
		for(unsigned i = 0; i < _genes.size(); ++i) {
			_genes[i].resize(_precision);
		}
	}
	~Chromosome();

	void geneDecode(vector<int>&);
	void distribute(int, int, vector<int>&);
	bool vote(const vector<int>&);

	int _order; // 1 is the smallest
	int _precision;
	int _nGene;
	int _nPlayers;
	vector< vector<bool> > _genes;
	int _gameResult;
	double _fitness;
};

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

bool Chromosome::vote(const vector<int>& dist) {
	//todo
	return true;
}

#endif