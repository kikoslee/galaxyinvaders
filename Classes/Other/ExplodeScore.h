#ifndef _ExplodeScore_H_
#define _ExplodeScore_H_

#include "DataType.h"

class ExplodeScore : public CCLabelTTF
{
public:
	ExplodeScore(CCPoint pos, int score, InvaderType type);
	
	void destroy();
};

#endif