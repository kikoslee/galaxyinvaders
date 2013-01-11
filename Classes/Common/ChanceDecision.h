#ifndef _ChanceDecision_H_
#define _ChanceDecision_H_

#include <map>

typedef std::map<int, int> ChanceMap;

class ChanceDecision
{
public:
	ChanceDecision();

	int makeDecision(int v);
	void addChance(int type, int v);
	void clear();

private:
	ChanceMap mOptions;
};

#endif