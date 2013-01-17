#include "Dialog.h"

void Dialog::_initWithType(DialogType type, const char* msg, CCNode* parent, int tag)
{
	_type = type;
	_func = NULL;
	_target = parent;

	initWithColorWidthHeight( ccc4(0,0,0,200), 480, 320);
	parent->addChild(this);

	createImage("dialog.png", ccpRatio(240, 200), this);
	
	if (type == dtNewMission)
	{
		createLabel(getLocalizedString("Next Mission"), gFontName, 16, gAnchorCenter, gColorBtn, ccpRatio(240, 220), this);
		createImage("icon_obj.png", ccpRatio(180, 195), this);
		createLabel(getCurObjName(), gFontName, 14, gAnchorLeft, ccYELLOW, ccpRatio(200, 200), this);
		createLabel(getCurObjDesc(), gFontName, 10, gAnchorLeft, gColorBtn, ccpRatio(200, 187), this);
	}
	else
	{
		CCLabelTTF* label = CCLabelTTF::labelWithString(msg, CCSizeMake(240,100), CCTextAlignmentCenter, gFontName, 14);
		label->setColor(gColorBtn);
		label->setPosition(ccp(240,200));
		addChild(label);
	}
	
	_menu = createMenu(this);
	CCMenuItem* item;
	if (type == dtAlert || type == dtNewMission)
	{
		item = createMenuItem("btn1.png", "btn1_d.png", ccpRatio(240, 120), 1000, _menu, this, menu_selector(Dialog::_menuCallback));
		addMenuLabel(item, getLocalizedString("CLOSE"), gFontName, 14, ccYELLOW);
	}
	else
	{
		item = createMenuItem("btn1.png", "btn1_d.png", ccpRatio(160, 120), 1000, _menu, this, menu_selector(Dialog::_menuCallback));
		addMenuLabel(item, getLocalizedString("YES"), gFontName, 14, ccYELLOW);
		item = createMenuItem("btn1.png", "btn1_d.png", ccpRatio(320, 120), 1001, _menu, this, menu_selector(Dialog::_menuCallback));
		addMenuLabel(item, getLocalizedString("NO"), gFontName, 14, ccYELLOW);
	}

	setIsTouchEnabled(true);
	autorelease();
}

Dialog::Dialog(DialogType type, const char* msg, CCNode* parent)
{
	_initWithType(type, msg, parent, 0);
}

Dialog::Dialog(DialogType type, const char* msg, CCNode* parent, int tag, SEL_CallFunc func)
{
	_initWithType(type, msg, parent, tag);
	_func = func;
}

void Dialog::_menuCallback(CCObject* sender)
{
	int index = ((CCMenuItem*)sender)->getZOrder();
	Audio->playEffect(EF_CLICK);

	if (_func)
	{
		if (index == 1000)
		{
			(_target->*_func)();
		}
	}

	removeFromParentAndCleanup(true);
}

void Dialog::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority+1, true);
}

bool Dialog::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
#if 0 //del by zhaoyi
	if(_menu->itemForTouch(touch))
		return false;
#endif
	return true;
}