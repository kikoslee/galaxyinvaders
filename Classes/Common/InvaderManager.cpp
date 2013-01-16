#include "InvaderManager.h"

InvaderManager::InvaderManager()
{
	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("invaders.png");
	_batch = CCSpriteBatchNode::createWithTexture(tex);
	addChild(_batch);
}

void InvaderManager::addNew(InvaderType type)
{
	InvaderBase* invader = new InvaderBase(type, _batch);
	invader->fire();
}
