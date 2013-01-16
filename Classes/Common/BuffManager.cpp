#include "BuffManager.h"

Buff::Buff(SpellType type)
{
    const SpellData& sd = GDShared->getSpell(type);
    
	_alreadyBlink = false;
	_type = type;
	_maxTime = sd.duration;
	_curTime = 0;
	
	HBcreateImageWithFrameName("ui_buff1.png", 0, 0, this);
	_icon = HBcreateImageWithFrameName(sd.iconName.c_str(), 0, 0, this);
	_lastTime = HBcreateLabel(fcs("%d", (int)_maxTime), gFontName, 32, gAnchorCenter, ccYELLOW, 0, 0, this);
}

Buff::~Buff()
{
}
	
bool Buff::updateBuff(float dt)
{
	_curTime += dt;
		
	if(_curTime >= _maxTime)
		return true;
	else if(_curTime >= _maxTime - 3 && !_alreadyBlink)
	{
		_icon->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCFadeTo::create(0.2, 50), CCFadeTo::create(0.2, 255), NULL)));
		_alreadyBlink = true;
	}
	
 	_lastTime->setString(fcs("%d", max(0, (int)(_maxTime - _curTime))));
		
	return false;
}
	
static int sBuffDistance = 80;

BuffManager::BuffManager()
{
	setAnchorPoint(ccp(0,0));
	setPosition(HBgetPositionByPercent(5, 90));
	autorelease();
}

BuffManager::~BuffManager()
{
}

void BuffManager::addBuff(SpellType type)
{
	Buff* newBuff = new Buff(type);
	
	// Search buff exist
	bool bFound = false;

	vector<Buff*>::iterator itr;
	for(itr = _buffs.begin(); itr != _buffs.end(); ++itr)
	{
		Buff* buff = *itr;
		if(buff->getType() == type)
		{
			removeChild(buff, true);
			*itr = newBuff;
			bFound = true;
			break;
		}
	}
	
	if(!bFound)
	{
		newBuff->setPosition(ccp(_buffs.size() * sBuffDistance, 0));
		_buffs.push_back(newBuff);
	}
	
	addChild(newBuff);
}

void BuffManager::updateBuff(float dt)
{
	int startPosX = 0;

	vector<Buff*>::iterator itr;
	for(itr = _buffs.begin(); itr != _buffs.end(); ++itr)
	{
		Buff* buff = *itr;
		if(buff->updateBuff(dt))
		{
			_buffs.erase(itr);
			removeChild(buff, true);
			break;
		}
		else
		{
			buff->setPosition(ccp(startPosX, 0));
			startPosX += sBuffDistance;
		}
	}
}
