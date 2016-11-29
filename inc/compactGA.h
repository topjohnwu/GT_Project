#ifndef _COMPACTGA_
#define _COMPACTGA_

#include <vector>
#include <iostream>
#include "chromosome.h"

using namespace std;

class CompactGA
{
public:
	// CompactGA(int, int, int); // <player number, population size>

	// Player, population size, genePrecision, resources, generation number
	void setParams(int, int, int, int, int);
	void runGA();
	void printCurrent(ostream&);

	void setPlayerNumber(int);
	void setPrecision(int);
	void setGeneration(int);
	void setPopSize(int);
	void setResNum(int);

protected:
	virtual void executeGame(vector<Chromosome*>&) = 0;
	void init();
	void fitness();
	void generate(); // generate new generation (reset genes of chromosome)
	bool checkTermCond();

	int _popSize;
	int _nGeneration;
	int _nPlayers;
	int _nResources;
	int _genePrecision;
	int _maxPrec; // 2^_genePrecision

	vector< vector<Chromosome> > _populations;
	vector< vector< vector<double> > > _probVec; // probability vector to generate new chromosomes)
};

#endif