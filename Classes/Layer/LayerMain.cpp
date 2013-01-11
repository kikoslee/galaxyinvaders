#include "LayerMain.h"
#include "LayerStoreLoader.h"
#include "GlobalData.h"

LayerMain::LayerMain()
: mLabelTitle(NULL)
, mLabelCurObjName(NULL)
, mLabelCurObjDesc(NULL)
, mBtnSound(NULL)
{
}

LayerMain::~LayerMain()
{
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mLabelCurObjName);
    CC_SAFE_RELEASE(mLabelCurObjDesc);
    CC_SAFE_RELEASE(mBtnSound);
}

void LayerMain::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelTitle->setString(gls("Current Mission"));
    mLabelCurObjName->setString(GDShared->getCurObjName());
    mLabelCurObjDesc->setString(GDShared->getCurObjDesc());

	_refreshSoundBtn();
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    return false;
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
	Audio->playEffect(EF_CLICK);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerStore", LayerStoreLoader::loader())));
}

void LayerMain::onBtnRank(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
//k    HBScore::showBoard("com.liho.galaxyinvaders.totalscore");
}

void LayerMain::onBtnMore(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
//k    HBWebBrowser::gotoUrl("itms-apps://itunes.com/apps/limin");
}