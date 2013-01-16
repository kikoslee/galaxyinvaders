#include "GlobalData.h"
#include "LayerMissionClear.h"

LayerMissionClear::LayerMissionClear()
: mLight1(NULL)
, mLight2(NULL)
, mLabelCurObjName(NULL)
, mLabelCurObjDesc(NULL)
, mLabelGold(NULL)
, mLabelMultiTitle(NULL)
, mLabelMulti(NULL)
, mLabelNextObjName(NULL)
, mLabelNextObjDesc(NULL)
, mBtnClose(NULL)
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCArray* frames = CCArray::createWithCapacity(4);
    frames->addObject(cache->spriteFrameByName("ani_light1.png"));
    frames->addObject(cache->spriteFrameByName("ani_light2.png"));
    frames->addObject(cache->spriteFrameByName("ani_light3.png"));
    frames->addObject(cache->spriteFrameByName("ani_light4.png"));
	
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 0.1f);
    mAniLight = CCAnimate::create(animation);
    mAniLight->retain();

    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(tp_dialog);
}

LayerMissionClear::~LayerMissionClear()
{
    mAniLight->release();

    CC_SAFE_RELEASE(mLight1);
    CC_SAFE_RELEASE(mLight2);
    CC_SAFE_RELEASE(mLabelCurObjName);
    CC_SAFE_RELEASE(mLabelCurObjDesc);
    CC_SAFE_RELEASE(mLabelGold);
    CC_SAFE_RELEASE(mLabelMultiTitle);
    CC_SAFE_RELEASE(mLabelMulti);
    CC_SAFE_RELEASE(mLabelNextObjName);
    CC_SAFE_RELEASE(mLabelNextObjDesc);
    CC_SAFE_RELEASE(mBtnClose);
}

SEL_MenuHandler LayerMissionClear::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerMissionClear::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClose", LayerMissionClear::onBtnClose);
    return NULL;
}

bool LayerMissionClear::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLight1", CCSprite*, mLight1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLight2", CCSprite*, mLight2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCurObjDesc", CCLabelTTF*, mLabelCurObjDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCurObjName", CCLabelTTF*, mLabelCurObjName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGold", CCLabelTTF*, mLabelGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMultiTitle", CCLabelTTF*, mLabelMultiTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMulti", CCLabelTTF*, mLabelMulti);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelNextObjName", CCLabelTTF*, mLabelNextObjName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelNextObjDesc", CCLabelTTF*, mLabelNextObjDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnClose", CCControlButton*, mBtnClose);
    return false;
}

void LayerMissionClear::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mBtnClose->setDefaultTouchPriority(tp_dialogBtn);
    
    GDShared->gold += 500;
    GDShared->multiplier ++;

    mBtnClose->setTitleForState(ccs(gls("Close")), CCControlStateNormal);
    
    mLabelGold->setString("+500");
    
    mLabelMultiTitle->setString(fcs("%s:", gls("Multiplier:")));
    mLabelMulti->setString("+1");
    
    mLabelCurObjName->setString(GDShared->getCurObjName());
    mLabelCurObjDesc->setString(GDShared->getCurObjDesc());
    
    // 下一任务
    if (GDShared->curObj < GDShared->getObjCount() - 1)
    {
        GDShared->curObj ++;
        mLabelNextObjName->setString(GDShared->getCurObjName());
        mLabelNextObjDesc->setString(GDShared->getCurObjDesc());
    }
    else
    {
        mLabelNextObjName->setString(gls("All mission are cleared"));
        mLabelNextObjDesc->setVisible(false);
    }
    
    GDShared->saveUserData();
    Audio->playEffect(EF_TASKFINISH);
    
    _aniLight1();
    _aniLight2();
}

void LayerMissionClear::onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    getParent()->removeChild(this, true);
}

void LayerMissionClear::_aniLight1()
{
    int xx = rand() % 20 + 110;
    float x = xx / 480.f * 100.f;
    int yy = rand() % 10 + 255;
    float y = yy / 320.f * 100.f;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    mLight1->setColor(ccc3(r, g, b));
    mLight1->setPosition(HBgetPositionByPercent(x, y));
    mLight1->runAction(CCSequence::create((CCFiniteTimeAction*)mAniLight->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(LayerMissionClear::_aniLight1)), NULL));
}

void LayerMissionClear::_aniLight2()
{
    int xx = rand() % 20 + 350;
    float x = xx / 480.f * 100.f;
    int yy = rand() % 10 + 255;
    float y = yy / 320.f * 100.f;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    mLight2->setColor(ccc3(r, g, b));
    mLight2->setPosition(HBgetPositionByPercent(x, y));
    mLight2->runAction(CCSequence::create((CCFiniteTimeAction*)mAniLight->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(LayerMissionClear::_aniLight2)), NULL));
}

bool LayerMissionClear::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
