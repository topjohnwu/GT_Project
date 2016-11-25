#ifndef _COMPACTGA_
#define _COMPACTGA_

#include <vector>
#include "Chromosome.h"

using namespace std;

class CompactGA
{
public:
	CompactGA();
	~CompactGA();

	void runGA();
	void printCurrent();

	void setPopulation(int);
	void setGeneration(int);
	void setPlayerNum(int);

private:
	void executeGame();
	void fitness();

	int _popSize;
	int _genSize;
	int _nPlayers;
	vector< vector<Chromosome> > _populations;
};

#endif