#ifndef _InvaderBase_H_
#define _InvaderBase_H_

#include "DataType.h"

// 初始化侵略者
void gCreateInvaders();
void gReleaseInvaders();

class InvaderBase : public CCSprite
{
	CCSpriteBatchNode*	_batch;
	CCPoint				_speed;
	bool				_active;
	InvaderType			_type;
	float				_radius;
    
public:
	InvaderBase(InvaderType type, CCSpriteBatchNode* batch);
	virtual ~InvaderBase() {};
	
	void fire();
	void destroy();
	void clear();

	/* 更新位置，如果出屏了，则返回false，否则返回true */
	bool updateInvader(float dt);

	int getScore();
	float getRadius() { return _radius; }
	InvaderType getType() { return _type; }

	bool isActive() { return _active; }
};

#endif