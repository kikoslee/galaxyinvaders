#include "GlobalData.h"
#include "LayerMissionClear.h"

LayerMissionClear::LayerMissionClear()
{
}

LayerMissionClear::~LayerMissionClear()
{
}

void LayerMissionClear::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
}

SEL_MenuHandler LayerMissionClear::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerMissionClear::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

bool LayerMissionClear::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return false;
}

/*
LayerMissionClear::~LayerMissionClear()
{
    mAniLight->release();
}

bool LayerMissionClear::init()
{
    // light
    mLight1 = createImageWithFrameName("ani_light1.png", 0, 0, this);
    mLight2 = createImageWithFrameName("ani_light1.png", 0, 0, this);

    frames = CCArray::createWithCapacity(4);
    frames->addObject(cache->spriteFrameByName("ani_light1.png"));
    frames->addObject(cache->spriteFrameByName("ani_light2.png"));
    frames->addObject(cache->spriteFrameByName("ani_light3.png"));
    frames->addObject(cache->spriteFrameByName("ani_light4.png"));
	
    animation = CCAnimation::createWithSpriteFrames(frames, 0.5f);
    mAniLight = CCAnimate::create(animation);
    mAniLight->retain();

    _aniLight1();
    _aniLight2();

    createLabel(GDShared->getCurObjName(), gFontName, 12, gAnchorLeft, ccYELLOW, 190, 227, this);
    CCLabelTTF* goalDesc = CCLabelTTF::create(GDShared->getCurObjDesc(), gFontName, 12, CCSizeRatio(200, 55), kCCTextAlignmentLeft);

    // 奖励
    GDShared->gold += 500;

    createLabel(getLocalizedString("Multiplier:"), gFontName, 12, CCPointZero, gColorBtn, 260, 155, this);
	
    GDShared->multiplier ++;
    createLabel("+1", gFontName, 24, CCPointZero, ccYELLOW, 330, 150, this);

    // 下一任务
    if (GDShared->curObj < GDShared->getObjCount() - 1)
    {
        GDShared->curObj ++;

        goal = createImageWithFrameName("icon_obj.png", 120, 100, this);
        goal->setScale(0.8);
        createLabel(GDShared->getCurObjName(), gFontName, 12, gAnchorLeft, ccYELLOW, 140, 107, this);
        goalDesc = CCLabelTTF::create(GDShared->getCurObjDesc(), gFontName, 12, CCSizeRatio(200, 55), kCCTextAlignmentLeft);
        goalDesc->setColor(gColorBtn);
        goalDesc->setAnchorPoint(ccp(0,0));
        goalDesc->setPosition(ccpRatio(140, 67));
        addChild(goalDesc);
    }
    else
    {
        createLabel(getLocalizedString("All mission are cleared"), gFontName, 16, gAnchorLeft, gColorBtn, 120, 100, this);
    }

    GDShared->saveUserData();

    mMenu = createMenu(this);

    CCMenuItem* item = createMenuItemWithCache("btn1.png", "btn1_d.png", 365,100, 1001, mMenu, this, menu_selector(LayerMissionClear::_menuCallback));
    addMenuLabel(item, getLocalizedString("Close"), gFontName, 16, ccWHITE);

    Audio->playEffect(EF_TASKFINISH);

    return true;
}

void LayerMissionClear::_aniLight1()
{
    int x = rand() % 20 + 110;
    int y = rand() % 10 + 255;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    mLight1->setColor(ccc3(r, g, b));
    mLight1->setPosition(ccpRatio(x, y));
    mLight1->runAction(CCSequence::create((CCFiniteTimeAction*)mAniLight->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(LayerMissionClear::_aniLight1)), NULL));
}

void LayerMissionClear::_aniLight2()
{
    int x = rand() % 20 + 350;
    int y = rand() % 10 + 255;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    mLight2->setColor(ccc3(r, g, b));
    mLight2->setPosition(ccpRatio(x, y));
    mLight2->runAction(CCSequence::create((CCFiniteTimeAction*)mAniLight->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(LayerMissionClear::_aniLight2)), NULL));
}

void LayerMissionClear::_menuCallback(CCObject* sender)
{
    Audio->playEffect(EF_CLICK);
    getParent()->removeChild(this, true);
}

//k
//void LayerMissionClear::registerWithTouchDispatcher()
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
//}

bool LayerMissionClear::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
//k
//	if (mMenu->itemForTouch(touch))
//		return false;

	return true;
	//返回yes是表明要取得该touch的权限,即吞噬该touch
	//返回NO 则不处理
}
*/