#include "LayerResult.h"
//#include "LayerMain.h"
//#include "LayerGame.h"
//#include "LayerStore.h"
//#include "GlobalData.h"
//#include "LayerBuy.h"
//#include "Dialog.h"
//#include "LayerMissionClear.h"

LayerResult::LayerResult()
{
}

LayerResult::~LayerResult()
{
}

void LayerResult::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
}

SEL_MenuHandler LayerResult::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerResult::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

bool LayerResult::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return false;
}

/*
bool LayerResult::init()
{
	_checkMission();
	_createLayer();
    
    GDShared->saveUserData();
	
	setTouchEnabled(true);
    scheduleUpdate();
    
//k    gUploadScore(gCurScore.score, gCurScore.lastTime);
    
    mCurTime = 0;
    mCurStep = 0;
    
	return true;
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
                SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
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
                SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
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
                SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
                mLabelInvaderCount[mCurStep]->setVisible(true);
                mLabelInvaderCount[mCurStep]->setScale(2);
                mLabelInvaderCount[mCurStep]->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
        case 0:
            if (mCurTime > 0.5)
            {
                SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
                mLabelInvaderCount[mCurStep]->setVisible(true);
                mLabelInvaderCount[mCurStep]->setScale(2);
                mLabelInvaderCount[mCurStep]->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1)));
                mCurTime = 0;
                mCurStep++;
            }
            break;
    }
    
    mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold)));
}

void LayerResult::_dialogReturn()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LayerStore::scene()));
}

void LayerResult::_menuCallback(CCObject* sender)
{
	int index = ((CCMenuItem*)sender)->getZOrder();
	
	SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
	
	switch(index)
	{
		case rmtContinue:
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LayerStore::scene()));
			break;
		case rmtGold:
		case rmtGift:
			{
				onExit();
				LayerBuy* buy = LayerBuy::create();
				CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
				scene->addChild(buy, 50000);
			}
			break;
	}
}

//k
//void LayerResult::registerWithTouchDispatcher()
//{
//	CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this, 0);
//}

bool LayerResult::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
	return false;
}

void LayerResult::_createLayer()
{
	// Invaders
	for(int i = 0; i < 4; i++)
	{
		const InvaderData& invaderData = GDShared->getInvader(type[i]);
			
		mLabelInvaderCount[i] = createLabel(fcs("x %d", GDShared->curInvadersCount[type[i]]), gFontName, 16, gAnchorLeft, gColorBtn, x+50, y-10, this);
        mLabelInvaderCount[i]->setVisible(false);
	}
	
	// Total Score
	mLabelScore = createLabel(fcs("%s", HBCommaPrint(GDShared->curScore)), gFontName, 26, CCPointZero, gColorBtn, 100, 115, this);
    mLabelScore->setVisible(false);
	
	// Last Time
	mLabelLastTime = createLabel(fcs("%ds", GDShared->curLastTime), gFontName, 26, CCPointZero, gColorBtn, 310, 115, this);
    mLabelLastTime->setVisible(false);
	
	mLabelGold = createLabel(fcs("%s", HBCommaPrint(GDShared->gold)), gFontName, 12, gAnchorRight, gColorBtn, 452, 302, this);
}

void LayerResult::_checkMission()
{
	if (GDShared->curObj < GDShared->getObjCount())
	{
		const Objective& obj = GDShared->getCurObj();
		
		if (obj.type == otScore)
		{
			if (GDShared->curScore * GDShared->multiplier >= obj.value)
				mMissionClear = true;
		}
		else if (obj.type == otLast)
		{
			if (GDShared->curLastTime >= obj.value)
				mMissionClear = true;
		}
		else if (obj.type == otGreen)
		{
			if (GDShared->curInvadersCount[IT_Normal_3] >= obj.value)
				mMissionClear = true;
		}
		else if (obj.type == otYellow)
		{
			if (GDShared->curInvadersCount[IT_Normal_4] >= obj.value)
				mMissionClear = true;
		}
		else if (obj.type == otTotal)
		{
			int invaderTotal = GDShared->curInvadersCount[IT_Normal_1] + GDShared->curInvadersCount[IT_Normal_2] + GDShared->curInvadersCount[IT_Normal_3] + GDShared->curInvadersCount[IT_Normal_4];
			if (invaderTotal >= obj.value)
				mMissionClear = true;
		}
	}
}

void LayerResult::_showMissionClear()
{
    LayerMissionClear* layer = LayerMissionClear::create();
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    scene->addChild(layer, 50000);
    _refreshView();
}

void LayerResult::_refreshView()
{
	mLabelMulti->setString(fcs("x%d", GDShared->multiplier));
    mGoalName->setString(GDShared->getCurObjName());
    mGoalDesc->setString(GDShared->getCurObjDesc());
}
*/