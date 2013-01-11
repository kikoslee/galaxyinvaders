#include "GlobalData.h"
#include "InvaderBase.h"

void gCreateInvaders()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("invaders.plist");
	
	for(int i = 0; i < INVADERS_COUNT; i++)
	{
		InvaderData& invader = GDShared->getInvader((InvaderType)i);
        invader.frameArr = CCArray::create();
        invader.frameArr->retain();
		
		if(invader.frameCount > 0)
		{
			for(int j = 0; j < invader.frameCount; j++)
			{		
				invader.frameArr->addObject(cache->spriteFrameByName(fcs("%s_%d.png", invader.fileName.c_str(), j+1)));
			}
		}
		else
		{
			invader.frameArr->addObject(cache->spriteFrameByName(fcs("%s.png", invader.fileName.c_str())));
		}
        
        CCAnimation* animation;
		if(invader.type == IT_Gold) 
		{
            animation = CCAnimation::createWithSpriteFrames(invader.frameArr, 0.03f);
		}
		else
		{
            animation = CCAnimation::createWithSpriteFrames(invader.frameArr, 0.3f);
		}
		
		invader.animation = CCRepeatForever::create(CCAnimate::create(animation));
		invader.animation->retain();
	}
}

void gReleaseInvaders()
{
	for(int i = 0; i < INVADERS_COUNT; i++)
	{
		GDShared->getInvader((InvaderType)i).animation->release();
	}
}


InvaderBase::InvaderBase(InvaderType type, CCSpriteBatchNode* batch)
{
    InvaderData& invader = GDShared->getInvader(type);
	initWithSpriteFrame((CCSpriteFrame*)invader.frameArr->objectAtIndex(0));
	
	_type = type;
	_active = false;
	_batch = batch;
	_radius = 40;

	// 出现的方位，上45%，左25%，右25%，下5%
	int direction = rand() % 100;
	
	CCPoint startPos, endPos;
	
	if(direction < 45)			// 上
	{
		startPos.x = rand() % 1000 - 100;
		startPos.y = 800;
		endPos.x = rand() % 500 + 300;
		endPos.y = -60;
	}
	else if(direction < 70)		// 左
	{
		startPos.x = -60;
		int top = rand() % 100;
		if(top < 75)		// 尽量出现在上部
			startPos.y = rand() % 400 + 320;
		else
			startPos.y = rand() % 400 - 60;
		endPos.x = 1100;
		endPos.y = rand() % 240 + 200;
	}
	else if(direction < 95)		// 右
	{
		startPos.x = 1100;
		int top = rand() % 100;
		if(top < 75)		// 尽量出现在上部
			startPos.y = rand() % 400 + 320;
		else
			startPos.y = rand() % 400 - 60;
		endPos.x = -60;
		endPos.y = rand() % 240 + 200;
	}
	else						// 下
	{
		startPos.x = rand() % 1000 + 40;
		startPos.y = -60;
		endPos.x = rand() % 500 + 300;
		endPos.y = 800;
	}
    
	CCPoint nml = ccpNormalize(ccpSub(endPos, startPos));
	float rotate = 90 - CC_RADIANS_TO_DEGREES(ccpToAngle(nml));
	float speed = rand() % 160 + 100;
	
	_speed.x = nml.x * speed;
	_speed.y = nml.y * speed;
	
	if(invader.animation != NULL)
	{
		CCAction* action = (CCAction*)invader.animation->copy()->autorelease();
		runAction(action);
	}
	
	setPosition(startPos);
	setRotation(rotate);
	
	if (_type == IT_Gold)
		setScale(0.5);
	
	autorelease();
}

void InvaderBase::fire()
{
	_active = true;
	_batch->addChild(this);
}

void InvaderBase::destroy()
{
	_active = false;
	setVisible(false);
	runAction(CCSequence::create(CCDelayTime::create(0.1), CCCallFunc::create(this, callfunc_selector(InvaderBase::clear)), NULL));
}

void InvaderBase::clear()
{
	stopAllActions();
	getParent()->removeChild(this, true);
}

int InvaderBase::getScore()
{
    InvaderData& invader = GDShared->getInvader(_type);
	if (_type == IT_Gold || _type == IT_Gold2)
		return invader.baseScore;
	else 
		return invader.baseScore * GDShared->multiplier;
}

bool InvaderBase::updateInvader(float dt)
{
	if(_active)
	{
		CCPoint pos = ccpAdd(getPosition(), ccpMult(_speed, dt * GDShared->curSpeedFactor));
		setPosition(pos);

		_radius	= 50;
	
		if(pos.x < -120 || pos.x > 1200 || pos.y < -120 || pos.y > 820)
		{
			destroy();
			return false;
		}
	}
	
	return true;
}
