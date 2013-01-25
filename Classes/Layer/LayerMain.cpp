#include "LayerMain.h"
#include "GlobalData.h"
#include "LayerStoreLoader.h"
#include "TotalGoldLoader.h"
#include "NextMissionLoader.h"
#include "DlgQuitLoader.h"

LayerMain::LayerMain()
: mLabelTitle(NULL)
, mLabelCurObjName(NULL)
, mLabelCurObjDesc(NULL)
, mBtnSound(NULL)
, mBtnRank(NULL)
{
    setKeypadEnabled(true);
}

LayerMain::~LayerMain()
{
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mLabelCurObjName);
    CC_SAFE_RELEASE(mLabelCurObjDesc);
    CC_SAFE_RELEASE(mBtnSound);
    CC_SAFE_RELEASE(mBtnRank);
}

SEL_MenuHandler LayerMain::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerMain::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnPlay", LayerMain::onBtnPlay);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnSound", LayerMain::onBtnSound);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnRank", LayerMain::onBtnRank);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnMore", LayerMain::onBtnMore);
    return NULL;
}

bool LayerMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCurObjName", CCLabelTTF*, mLabelCurObjName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCurObjDesc", CCLabelTTF*, mLabelCurObjDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnSound", CCControlButton*, mBtnSound);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnRank", CCControlButton*, mBtnRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    return false;
}

void LayerMain::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelTitle->setString(gls("Current Mission"));
    mLabelCurObjName->setString(GDShared->getCurObjName());
    mLabelCurObjDesc->setString(GDShared->getCurObjDesc());
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    mBtnRank->setVisible(false);
#else
#endif
	_refreshSoundBtn();
}

void LayerMain::_refreshSoundBtn()
{
    if (GDShared->isMusicOn)
    {
        mBtnSound->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_sound_on.png"), CCControlStateNormal);
    }
    else
    {
        mBtnSound->setBackgroundSpriteFrameForState(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_sound_off.png"), CCControlStateNormal);
    }
    Audio->setBackgroundMusicVolume(GDShared->isMusicOn ? 0.7 : 0);
    Audio->setEffectsVolume(GDShared->isMusicOn ? 1 : 0);
}

void LayerMain::onBtnSound(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    GDShared->isMusicOn = !GDShared->isMusicOn;
    GDShared->saveUserData();
    _refreshSoundBtn();
}

void LayerMain::onBtnPlay(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBUmeng::event("Button", "MainPlay");
	Audio->playEffect(EF_CLICK);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerStore", LayerStoreLoader::loader())));
}

void LayerMain::onBtnRank(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#else
    HBScore::showBoard("com.liho.galaxyinvaders.totalscore");
#endif
}

void LayerMain::onBtnMore(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBUmeng::event("Button", "MainMore");
	Audio->playEffect(EF_CLICK);
    gotoMoreGame();
}

//for android
void LayerMain::keyBackClicked()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if (!gIsDlgQuitShow)
    {
        gIsDlgQuitShow = true;
        CCDirector::sharedDirector()->getRunningScene()->addChild(HBLayerLoader("DlgQuit", DlgQuitLoader::loader()));
    }
#endif // CC_PLATFORM_ANDROID
}
