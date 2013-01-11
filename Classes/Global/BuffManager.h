#ifndef _BuffManager_H_
#define _BuffManager_H_

#include "GlobalData.h"
#include "SpellSlot.h"

class Buff : public CCNode
{
	CCSprite* _icon;
	CCLabelTTF* _lastTime;
	SpellType _type;
	float _maxTime;
	float _curTime;
	bool _alreadyBlink;
	
public:
	Buff(SpellType type);
	virtual ~Buff();
	
	SpellType getType() { return _type; }
	
	bool updateBuff(float dt);
};

class BuffManager : public CCNode
{
	vector<Buff*> _buffs;
	
public:
	BuffManager();
	virtual ~BuffManager();
	
	void addBuff(SpellType type);
	void updateBuff(float dt);
};

#endif
