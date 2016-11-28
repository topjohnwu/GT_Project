#ifndef _COMPACTGA_
#define _COMPACTGA_

#include <vector>
#include <iostream>
#include "chromosome.h"

using namespace std;

class CompactGA
{
public:
	CompactGA(int, int, int); // <player number, population size>

	void runGA();
	void printCurrent(ostream&);

	void setGeneration(int);
	void setResNum(int);

protected:
	virtual void executeGame() = 0;
	void fitness();
	void generate(); // generate new generation (reset genes of chromosome)

	int _popSize;
	int _genSize;
	int _nPlayers;
	int _nResources;
	int _genePrecision;
	int _maxPrec; // 2^_genePrecision

	vector< vector<Chromosome> > _populations;
	vector< vector<double> > _probVec; // probability vector to generate new chromosomes)
	vector< vector<int> > _results;
};

#endif