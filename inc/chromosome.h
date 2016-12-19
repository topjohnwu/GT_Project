#ifndef _CHROMOSOME_
#define _CHROMOSOME_

#include <vector>
#include <iostream>

using namespace std;

class Chromosome
{
public:
	Chromosome() {};
	void init(int, int, int, int);
	vector<int> geneDecode();
	void distribute(int, int, vector<int>&);
	bool vote(int, const vector<int>&);
	void setGenes(const vector< vector<double> >&);

	int _order; // 1 is the smallest
	int _precision;
	int _nGene;
	int _nPlayers;
	int _nRes;
	int _gameResult;
	vector< vector<bool> > _genes; //[distribute value[_order-1], vote strategy[_nplayers+1]] 
	// double _fitness;
};

#endif