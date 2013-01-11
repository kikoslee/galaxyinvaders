#include "GlobalData.h"
#include "SpellSlot.h"
#include "CommonHelper.h"

Spell::Spell(SpellType type)
{
	_casted = false;
	_type = type;
	
    const SpellData& info = GDShared->getSpell(type);
	_icon = CCSprite::createWithSpriteFrameName(info.fileName.c_str());
	_icon->setOpacity(200);
	addChild(_icon);

	if (GDShared->getSpellCount(_type) > 0)
		_icon->setColor(ccWHITE);
	else
		_icon->setColor(ccGRAY);
	

	_progress = CCProgressTimer::create(CCSprite::createWithSpriteFrameName(info.fileName.c_str()));
	_progress->setType( kCCProgressTimerTypeRadial );
	_progress->setVisible(false);
	addChild(_progress);
	
	_labelCount = HBcreateLabelAtlas(fcs("%d", GDShared->getSpellCount(_type)), "fnt-number.png", 20, 26, '0', 0, 80, gAnchorCenter, _icon, false);
	
	update(0);

	autorelease();
}

Spell::~Spell()
{
	if (_icon)
		_icon->stopAllActions();
}

bool Spell::checkClick(CCTouch* touch)
{
	CCPoint pos = convertTouchToNodeSpace(touch);
	CCSize sizeSpell = _icon->getContentSize();
	CCRect rc = CCRectMake(-sizeSpell.width / 2, -sizeSpell.height / 2, sizeSpell.width, sizeSpell.height);
	
	return (GDShared->getSpellCount(_type) > 0) && rc.containsPoint(pos);
}

float Spell::getDuration()
{
    return GDShared->getSpell(_type).duration;
}

void Spell::cast()
{
	if (_isInCD)
		return;
	
	if (GDShared->getSpellCount(_type) > 0)
	{
		GDShared->spellCount[_type] --;
		_labelCount->setString(fcs("%d", GDShared->spellCount[_type]));
		_casted = true;
		
		if (GDShared->spellCount[_type] > 0)
			_icon->setColor(ccWHITE);
		else
			_icon->setColor(ccGRAY);
		
		float cdTime = GDShared->getSpell(_type).cdTime[GDShared->spellLevel[_type]];
		if (cdTime > 0)
		{
			_isInCD = true;
			_castTime = 0;
			
			_progress->setVisible(true);
			_progress->setPercentage(0);
			_progress->runAction(CCProgressTo::create(cdTime, 100));
		}

		setScale(1.3);
		runAction(CCSequence::create(CCScaleTo::create(0.1f, 0.9f), CCScaleTo::create(0.1f, 1.1f), CCScaleTo::create(0.1f, 1.0f), CCCallFunc::create(this, callfunc_selector(Spell::castFinish)), NULL));
	}
}

void Spell::castFinish()
{
}

void Spell::update(float dt)
{
	if (_isInCD)
	{
		_castTime += dt;
		
		float cdTime = GDShared->getSpell(_type).cdTime[GDShared->spellLevel[_type]];
		
		if (_castTime >= cdTime)
		{
			_isInCD = false;
			_progress->setVisible(false);
		}
	}
}

SpellSlot::SpellSlot(CCNode* parent, int zOrder)
{
	SpellType spell[3] = { ST_Freeze, ST_Shield, ST_Bomb };
	for(int i = 0; i < 3; i++)
	{
		_spells[i] = new Spell(spell[i]);
		_spells[i]->setPosition(ccp(0, -120*(i-1)));
		addChild(_spells[i]);
	}

	setPosition(HBgetPositionByPercent(12.5, 50));
	
	if (zOrder == 0)
		parent->addChild(this);
	else
		parent->addChild(this, zOrder);
	
	autorelease();
}

SpellSlot::~SpellSlot()
{
}

int SpellSlot::checkClick(CCTouch* touch)
{
	for(int i = 0; i < 3; i++)
	{
		if(_spells[i]->checkClick(touch))
			return i;
	}
	
	return -1;
}

void SpellSlot::cast(int idx)
{
	_spells[idx]->cast();
}

CCPoint SpellSlot::spellPos(int idx)
{
	return ccpAdd(getPosition(), _spells[idx]->getPosition());
}

Spell* SpellSlot::getSpell(int idx)
{
	return _spells[idx];
}

void SpellSlot::update(float dt)
{
	for(int i = 0; i < 3; i++)
		_spells[i]->update(dt);
}
