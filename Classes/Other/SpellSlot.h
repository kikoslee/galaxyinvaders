#ifndef _SpellSlot_H_
#define _SpellSlot_H_

#include "DataType.h"

class Spell : public CCNode
{
	CCSprite*		_icon;
	CCProgressTimer* _progress;
	CCLabelAtlas*	_labelCount;

	bool			_casted;		// 是否已经发动
	SpellType		_type;			// 类型
	float			_castTime;		// 释放时间
	bool			_isInCD;		// 冷却是否结束
	
public:
	Spell(SpellType type);
	virtual ~Spell();
	
	SpellType getType() { return _type; }
	float getDuration();
	const char* getSpellName();
	const char* getFileName();
	const char* getDesc();
	const char* getDurationStr();
		
	bool checkClick(CCTouch* touch);

	void cast();
	void castFinish();
	
	void update(float dt);
};

class SpellSlot : public CCNode
{
	Spell* _spells[3];

	SpellSlot() {}
	
public:
	SpellSlot(CCNode* parent, int zOrder = 0);
	virtual ~SpellSlot();
	
	virtual void update(float dt);
	
	Spell* getSpell(int index);
	int checkClick(CCTouch* touch);
	void cast(int index);
	CCPoint spellPos(int index);
};

#endif