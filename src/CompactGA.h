#ifndef _COMPACTGA_
#define _COMPACTGA_

#include <vector>
#include <iostream>
#include "Chromosome.h"

using namespace std;

class CompactGA
{
public:
	CompactGA();
	~CompactGA();

	void runGA();
	void printCurrent(ostream&);

	void setPopulation(int);
	void setGeneration(int);
	void setPlayerNum(int);
	void setResNum(int);

private:
	void executeGame();
	void fitness();
	void generate(); // generate new generation (reset genes of chromosome)

	int _popSize;
	int _genSize;
	int _nPlayers;
	int _nResources;
	vector< vector<Chromosome> > _populations;
	vector<double> _probVec; // probability vector to generate new chromosomes)
};

#endif