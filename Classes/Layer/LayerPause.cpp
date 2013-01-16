#include "LayerPause.h"
//#include "LayerGame.h"
#include "LayerStoreLoader.h"
#include "LayerHelpLoader.h"
#include "GlobalData.h"

LayerPause::LayerPause()
: mLabelCurrentMission(NULL)
, mLabelMissionName(NULL)
, mLabelMissionDesc(NULL)
, mLabelAllInvaders(NULL)
, mBtnSound(NULL)
, mBtnExit(NULL)
, mBtnContinue(NULL)
{
    for (int i = 0; i < 5; i++)
        mLabelCount[i] = NULL;
}

LayerPause::~LayerPause()
{
    CC_SAFE_RELEASE(mLabelCurrentMission);
    CC_SAFE_RELEASE(mLabelMissionName);
    CC_SAFE_RELEASE(mLabelMissionDesc);
    CC_SAFE_RELEASE(mLabelAllInvaders);
    for (int i = 0; i < 5; i++)
        CC_SAFE_RELEASE(mLabelCount[i]);
    CC_SAFE_RELEASE(mBtnSound);
    CC_SAFE_RELEASE(mBtnExit);
    CC_SAFE_RELEASE(mBtnContinue);
}

SEL_MenuHandler LayerPause::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerPause::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnHelp", LayerPause::onBtnHelp);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnSound", LayerPause::onBtnSound);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnExit", LayerPause::onBtnExit);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnContinue", LayerPause::onBtnContinue);
    return NULL;
}

bool LayerPause::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCurrentMission", CCLabelTTF*, mLabelCurrentMission);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMissionName", CCLabelTTF*, mLabelMissionName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMissionDesc", CCLabelTTF*, mLabelMissionDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelAllInvaders", CCLabelTTF*, mLabelAllInvaders);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount1", CCLabelTTF*, mLabelCount[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount2", CCLabelTTF*, mLabelCount[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount3", CCLabelTTF*, mLabelCount[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount4", CCLabelTTF*, mLabelCount[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount5", CCLabelTTF*, mLabelCount[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnSound", CCControlButton*, mBtnSound);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnExit", CCControlButton*, mBtnExit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnContinue", CCControlButton*, mBtnContinue);

    return false;
}

void LayerPause::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelCurrentMission->setString(gls("Current Mission"));
    mLabelMissionName->setString(GDShared->getCurObjName());
    mLabelMissionDesc->setString(GDShared->getCurObjDesc());
    mLabelAllInvaders->setString(gls("All Invaders"));

    mBtnExit->setTitleForState(ccs(gls("Quit")), CCControlStateNormal);
    mBtnContinue->setTitleForState(ccs(gls("Continue")), CCControlStateNormal);
    
	for( int i = 0; i < INVADERS_COUNT - 2; i++)
        mLabelCount[i]->setString(fcs("x %d", GDShared->curInvadersCount[i]));
}

void LayerPause::onBtnSound(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    
}

void LayerPause::onBtnHelp(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    LayerHelp* layer = (LayerHelp*)HBLayerLoader("LayerHelp", LayerHelpLoader::loader());
    layer->setInGame(true);
    getParent()->addChild(layer, 30000);
}

void LayerPause::onBtnExit(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    Audio->playBackgroundMusic(MUSIC_BG1, true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerStore", LayerStoreLoader::loader())));
}

void LayerPause::onBtnContinue(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);

    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    CCArray* layers = scene->getChildren();
    CCObject* child = NULL;
    CCARRAY_FOREACH(layers, child)
    {
        CC_BREAK_IF(!child);
        CCLayer* layer =(CCLayer*)child;
        if(!layer->isRunning())
            layer->onEnter();
    }
    scene->removeChild(this, true);
}
