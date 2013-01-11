#ifndef _Dialog_H_
#define _Dialog_H_

#include "DataType.h"

enum DialogType
{
	dtAlert,
	dtYesNo,
	dtNewMission,
};

class Dialog : public CCLayerColor
{
	DialogType _type;
	SEL_CallFunc _func;
	CCObject* _target;
	CCMenu* _menu;
	int _tag;

	void _initWithType(DialogType type, const char* msg, CCNode* parent, int tag);

	void _menuCallback(CCObject* sender);

public:
	Dialog(DialogType type, const char* msg, CCNode* parent);
	Dialog(DialogType type, const char* msg, CCNode* parent, int tag, SEL_CallFunc func);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
};

#endif