#ifndef _Devourer_H_
#define _Devourer_H_

#include "InvaderBase.h"

class Devourer : public CCNode
{
	CCSprite* _devourer;
	CCSprite* _shield;
	CCParticleSystem* _emitter;
	float _radius;

public:	
	Devourer();
	virtual ~Devourer() {};
	
	bool isShieldOn() { return _shield->isVisible(); }
	bool isContainPoint(CCPoint pos);
	void enableShield();
	void disableShield();
	void setDevourerPos(CCPoint pos);
	bool checkCollision(InvaderBase* ib);
};

#endif