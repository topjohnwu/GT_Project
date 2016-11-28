#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>

using namespace std;

class Chromosome
{
public:
	void init(int, int, int);
	vector<int> geneDecode();
	void distribute(int, int, vector<int>&);
	bool vote(int, const vector<int>&);

	int _order; // 1 is the smallest
	int _precision;
	int _nGene;
	int _nPlayers;
	vector< vector<bool> > _genes; //[distribute value[_order-1], vote strategy[_nplayers+1]] 
	double _fitness;
};

#endif