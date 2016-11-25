#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>

using namespace std;

class Chromosome
{
	friend class CompactGA;

	Chromosome();
	~Chromosome();

	vector<bool> _genes;
	int _gameResult;
	double _fitness;
};

#endif