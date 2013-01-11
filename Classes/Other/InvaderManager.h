#ifndef _InvaderManager_H_
#define _InvaderManager_H_

#include "InvaderBase.h"

class InvaderManager : public CCNode
{
	CCSpriteBatchNode* _batch;

public:
	InvaderManager();
	
	void addNew(InvaderType type);
	
	CCSpriteBatchNode* getBatch() { return _batch; }
};

#endif