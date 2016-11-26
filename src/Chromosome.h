#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>

using namespace std;

#define GENENUM 6

class Chromosome
{
	friend class CompactGA;

	Chromosome();
	~Chromosome();

	void geneDecode(vector<int>&);

	int _precision;
	vector< vector<bool> > _genes;
	int _gameResult;
	double _fitness;
};

void Chromosome::geneDecode(vector<int>& res) {
	for(unsigned i = 0; i < GENENUM; ++i) {
		int temp = 0;
		for(unsigned j = 0; j < _precision; ++j) {
			temp *= 2;
			temp += _genes[i][j];
		}
		res.push_back(temp);
	}
}

#endif