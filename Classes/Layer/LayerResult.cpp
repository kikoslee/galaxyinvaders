#include "LayerResult.h"
#include "GlobalData.h"
#include "LayerStoreLoader.h"
#include "LayerMissionClearLoader.h"

LayerResult::LayerResult()
: mLabelScore(NULL)
, mLabelLastTime(NULL)
, mLabelGold(NULL)
, mLabelTitle(NULL)
, mBtnContinue(NULL)
{
    for (int i = 0; i < 4; i++)
        mLabelCount[i] = NULL;
}

LayerResult::~LayerResult()
{
    CC_SAFE_RELEASE(mLabelScore);
    CC_SAFE_RELEASE(mLabelLastTime);
    CC_SAFE_RELEASE(mLabelGold);
    CC_SAFE_RELEASE(mLabelTitle);
    for (int i = 0; i < 4; i++)
        CC_SAFE_RELEASE(mLabelCount[i]);
}

SEL_MenuHandler LayerResult::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerResult::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnContinue", LayerResult::onBtnContinue);
    return NULL;
}

bool LayerResult::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount1", CCLabelTTF*, mLabelCount[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount2", CCLabelTTF*, mLabelCount[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount3", CCLabelTTF*, mLabelCount[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelCount4", CCLabelTTF*, mLabelCount[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelScore", CCLabelTTF*, mLabelScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelLastTime", CCLabelTTF*, mLabelLastTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGold", CCLabelTTF*, mLabelGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnContinue", CCControlButton*, mBtnContinue);
    return false;
}

void LayerResult::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	_checkMission();
    
	// Invaders
	for(int i = 0; i < 4; i++)
	{
		mLabelCount[i]->setString(fcs("x %d", GDShared->curInvadersCount[i]));
        mLabelCount[i]->setVisible(false);
	}
    
    mLabelTitle->setString(gls("Result"));
    
	// Total Score
	mLabelScore->setString(fcs("%s: %s", gls("Score"), HBCommaPrint(GDShared->curScore)));
    mLabelScore->setVisible(false);
    
	// Last Time
	mLabelLastTime->setString(fcs("%s: %ds", gls("Survival"), GDShared->curLastTime));
    mLabelLastTime->setVisible(false);
    
    mBtnContinue->setTitleForState(ccs(gls("Continue")), CCControlStateNormal);

	// TotalGold
	mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold)));

    GDShared->saveUserData();
	
    scheduleUpdate();
    
    HBScore::reportScore("com.liho.galaxyinvaders.totalscore", GDShared->curScore);
    HBScore::reportScore("com.liho.galaxyinvaders.survivaltime", GDShared->curLastTime);
    
    mCurTime = 0;
    mCurStep = 0;
}

void LayerResult::onBtnContinue(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerStore", LayerStoreLoader::loader())));
}

void LayerResult::_checkMission()
{
	if (GDShared->curObj < GDShared->getObjCount())
	{
		const Objective& obj = GDShared->getCurObj();
		
		if ((obj.type == otScore && GDShared->curScore * GDShared->multiplier >= obj.value) ||
            (obj.type == otLast && GDShared->curLastTime >= obj.value) ||
            (obj.type == otGreen && GDShared->curInvadersCount[IT_Normal_3] >= obj.value) ||
            (obj.type == otYellow && GDShared->curInvadersCount[IT_Normal_4] >= obj.value) ||
            (obj.type == otTotal && (GDShared->curInvadersCount[IT_Normal_1] + GDShared->curInvadersCount[IT_Normal_2] + GDShared->curInvadersCount[IT_Normal_3] + GDShared->curInvadersCount[IT_Normal_4]) >= obj.value))
				mMissionClear = true;
	}
}

void LayerResult::update(float dt)
{
    mCurTime += dt;
    
    switch (mCurStep)
    {
        case 6:     // 任务达成
            if (mCurTime > 0.5 && mMissionClear)
            {
                _showMissionClear();
                mCurStep++;
            }
            break;
        case 5:     // 时间出现
            if (mCurTime > 0.3)
            {
                Audio->playEffect(EF_CLICK);
                mLabelLastTime->setVisible(true);
                mLabelLastTime->setScale(2);
                mLabelLastTime->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
        case 4:     // 分数出现
            if (mCurTime > 0.3)
            {
                Audio->playEffect(EF_CLICK);
                mLabelScore->setVisible(true);
                mLabelScore->setScale(2);
                mLabelScore->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
        case 3:     // 0~3:4个数量出现
        case 2:
        case 1:
            if (mCurTime > 0.15)
            {
                Audio->playEffect(EF_CLICK);
                mLabelCount[mCurStep]->setVisible(true);
                mLabelCount[mCurStep]->setScale(2);
                mLabelCount[mCurStep]->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
        case 0:
            if (mCurTime > 0.5)
            {
                Audio->playEffect(EF_CLICK);
                mLabelCount[mCurStep]->setVisible(true);
                mLabelCount[mCurStep]->setScale(2);
                mLabelCount[mCurStep]->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
    }
    
    mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold)));
}

void LayerResult::_showMissionClear()
{
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(HBLayerLoader("LayerMissionClear", LayerMissionClearLoader::loader()), 50000);
}

