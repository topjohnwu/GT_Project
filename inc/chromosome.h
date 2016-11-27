#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>

using namespace std;

class Chromosome
{
	friend class CompactGA;

	Chromosome(int, int, int);
	~Chromosome();

	void geneDecode(vector<int>&);
	void distribute(int, int, vector<int>&);
	bool vote(int, const vector<int>&);

	int _order; // 1 is the smallest
	int _precision;
	int _nGene;
	int _nPlayers;
	vector< vector<bool> > _genes; //[distribute value[_order-1], vote strategy[_nplayers+1]] 
	int _gameResult;
	double _fitness;
};

#endif