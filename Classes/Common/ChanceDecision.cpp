#include "ChanceDecision.h"
#include <algorithm>

ChanceDecision::ChanceDecision()
{
}

int ChanceDecision::makeDecision(int v)
{
	int nearest = 999999999;
	int rtn = -1;

	ChanceMap::iterator mapItr;

	for( mapItr = mOptions.begin();	mapItr != mOptions.end(); ++mapItr)
	{
		if(mapItr->second > 0)
		{
			int random = rand() % mapItr->second + 1;
			if(nearest - v > random - v)
			{
				rtn = mapItr->first;
				nearest = random;
			}
		}
	}

	return rtn;
}

void ChanceDecision::addChance(int type, int v)
{
	mOptions[type] = v;
}

void ChanceDecision::clear()
{
	mOptions.clear();
}