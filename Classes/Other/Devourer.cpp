#include "Devourer.h"

Devourer::Devourer()
{
	_radius = 10;

	_emitter = CCParticleSystemQuad::create("particle_devourer.plist");
	_emitter->setPosition(CCPointZero);
	addChild(_emitter);

    _devourer = HBcreateImageWithFrameName("devourer.png", 0, 0, this);
	_devourer->runAction(CCRepeatForever::create(CCRotateBy::create(1, -360)));

	_shield = HBcreateImageWithFrameName("shield.png", 0, 0, this);
	_shield->setVisible(false);

}

bool Devourer::isContainPoint(CCPoint pos)
{
	return ccpDistance(getPosition(), pos) <= _radius * 3;
}

void Devourer::enableShield()
{
	_radius = 15;
	_shield->setVisible(true);
}

void Devourer::disableShield()
{
	_radius = 10;
	_shield->setVisible(false);
}

void Devourer::setDevourerPos(CCPoint pos)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(pos.x < 100)
		pos.x = 100;
	else if(pos.x > size.width)
		pos.x = size.width;
	
	if(pos.y < 0)
		pos.y = 0;
	else if(pos.y > size.height)
		pos.y = size.height;
	
	setPosition(pos);
}

bool Devourer::checkCollision(InvaderBase* ib)
{
	return ccpDistance(getPosition(), ib->getPosition()) <= _radius + ib->getRadius();
}
