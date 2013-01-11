#include "GlobalData.h"
#include "LayerGame.h"
#include "LayerPause.h"
#include "LayerResult.h"
#include "ExplodeScore.h"
#include "CommonHelper.h"

enum LayerZOrder
{
	lzo_bg,
	lzo_invaders,
	lzo_devourer,
	lzo_score,
	lzo_spell,
	lzo_menu,
};


float sEmitStart = 0.3;			// 初始发射频率
float sEmitLevel = 0.005;		// 发射频率每级别变化系数
float sEmitSubLevel = 0.001;	// 发射频率每子级别变化系数

// 生成几率, 初始值, 每级变化
int sChanceTable[INVADERS_COUNT][2] =
{
	{    30,   0 },		// IT_Normal_1
	{    80,   0 },		// IT_Normal_2
	{   100,   0 },		// IT_Normal_3
	{   200,   0 },		// IT_Normal_4
	{   80,   -3 },		// IT_Bad
	{   200,   0 },		// IT_Gold
	{	300,   0 },		// IT_Gold2
};	

LayerGame::LayerGame()
: mLabelLifeCount(NULL)
, mLabelGold(NULL)
, mLabelScore(NULL)
, mLabelTime(NULL)
, mLayerGame(NULL)
, mReady(NULL)
, mGo(NULL)
, mFinish(NULL)
, mTouch(NULL)
, mActionBlink(NULL)
, mActionSpeed(NULL)
, mActionShield(NULL)
, mActionMiss(NULL)
{
	setTouchEnabled(true);
    
	mActionMiss = CCSequence::create(CCScaleTo::create(0.3, 1), CCRotateTo::create(0.05, -15), CCRotateTo::create(0.05, 15), CCRotateTo::create(0.05, -15), CCRotateTo::create(0.05, 15), CCRotateTo::create(0.05, -15), CCRotateTo::create(0.05, 15), CCScaleTo::create(0.3, 0), CCHide::create(), NULL);
	mActionMiss->retain();
    
	mActionBlink = CCSequence::create(CCBlink::create(1, 10), CCShow::create(), NULL);
	mActionBlink->retain();
}

LayerGame::~LayerGame()
{
    CC_SAFE_RELEASE(mLabelLifeCount);
    CC_SAFE_RELEASE(mLabelGold);
    CC_SAFE_RELEASE(mLabelScore);
    CC_SAFE_RELEASE(mLabelTime);
    CC_SAFE_RELEASE(mLayerGame);
    CC_SAFE_RELEASE(mReady);
    CC_SAFE_RELEASE(mGo);
    CC_SAFE_RELEASE(mFinish);
    CC_SAFE_RELEASE(mActionBlink);
    CC_SAFE_RELEASE(mActionMiss);
}

SEL_MenuHandler LayerGame::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerGame::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnPause", LayerGame::onBtnPause);
    return NULL;
}

bool LayerGame::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelLifeCount", CCLabelTTF*, mLabelLifeCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGold", CCLabelTTF*, mLabelGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelScore", CCLabelTTF*, mLabelScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTime", CCLabelTTF*, mLabelTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerGame", CCLayer*, mLayerGame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLifes", CCSprite*, mLifes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mReady", CCSprite*, mReady);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGo", CCSprite*, mGo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFinish", CCSprite*, mFinish);
    return false;
}

void LayerGame::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    // Invaders
    mInvaders = new InvaderManager;
    mLayerGame->addChild(mInvaders, lzo_invaders);

    // Devourer
    mDevourer = new Devourer;
    mDevourer->setPosition(HBgetPositionByPercent(50, 50));
    mLayerGame->addChild(mDevourer, lzo_devourer);
    
    // Score
    mLayerExplodeScore = CCLayer::create();
    mLayerGame->addChild(mLayerExplodeScore, lzo_score);

    // Spell slot
    mSpell = new SpellSlot(this, lzo_spell);
    
    // Buff
    mBuff = new BuffManager;
    addChild(mBuff, lzo_spell);
    
	mLifeCount = GDShared->maxLife;
    mLabelLifeCount->setString(fcs("x %d", mLifeCount));

    // 金币总数
	mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold)));

    mLifes->runAction(CCRepeatForever::create(CCRotateBy::create(1, -360)));
    
	mReady->runAction(CCSequence::create(CCDelayTime::create(0.3), CCShow::create(), CCMoveTo::create(0.2, HBgetPositionByPercent(50, 50)), CCDelayTime::create(0.5), CCMoveTo::create(0.2, HBgetPositionByPercent(-20, 50)), NULL));
    
	mGo->runAction(CCSequence::create(CCDelayTime::create(1.7), CCShow::create(), CCMoveTo::create(0.2, HBgetPositionByPercent(50, 50)), CCDelayTime::create(1), CCMoveTo::create(0.2, HBgetPositionByPercent(50, 120)), NULL));
    
	Audio->playBackgroundMusic(MUSIC_BG2, true);
    
	// 初始化参数
    GDShared->clearCurGameData();
    for(int i = 0; i < INVADERS_COUNT; i++)
		mChance.addChance(i, sChanceTable[i][0]);
	mTimePassed = 0;
    mLevel = 0;
	mSubLevel = 0;
	mStarted = false;
	mFinished = false;
	
	mEmitRate = sEmitStart;
	mEmitTime = 0;

	mDevourer->runAction(CCSequence::create(CCDelayTime::create(2.1f), CCCallFunc::create(this, callfunc_selector(LayerGame::_startGame)), NULL));
}

void LayerGame::onBtnPause(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    if(!mStarted)
		return;
	
	Audio->playEffect(EF_CLICK);
//	getParent()->addChild(LayerPause::create(), 10000);
}

void LayerGame::_startGame()
{
	mStarted = true;
	schedule(schedule_selector(LayerGame::_levelup), 1);
	scheduleUpdate();
}

void LayerGame::_levelup(float dt)
{
	mSubLevel++;
	mEmitRate -= sEmitSubLevel;
	
	if(mSubLevel == 10)
	{
		mLevel ++;
		if(mLevel == 24)
		{
			unschedule(schedule_selector(LayerGame::_levelup));
			return;
		}
		
		mEmitRate -= sEmitLevel;
		mSubLevel = 0;
	}
	
	if(mEmitRate < 0.2)
		mEmitRate = 0.2;
}

void LayerGame::update(float dt)
{
	mTimePassed += dt;
	mEmitTime += dt;
    
	while(mEmitTime >= mEmitRate)
	{
		mEmitTime -= mEmitRate;
		int type = mChance.makeDecision(1);
		GDShared->curGenerateCount[type]++;
		mInvaders->addNew((InvaderType)type);
	}
    
	_updateInvader(dt);
	mBuff->updateBuff(dt);
    
	mLabelScore->setString(fcs("%s", HBCommaPrint(GDShared->curScore)));
	mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold)));
	
	int sec;
	sec =  (int)mTimePassed;
    const char* tmp;
	
	if(sec >= 3600)
	{
		int hour = sec / 3600;
		sec %= 3600;
        tmp = fcs("%d:%02d:%02d", hour,sec/60,sec%60);
	}
	else
	{
        tmp = fcs("%d:%02d", sec/60,sec%60);
	}
	mLabelTime->setString(tmp);
	
	mSpell->update(dt);
}

void LayerGame::_updateInvader(float dt)
{
	CCArray* arrInvaders = mInvaders->getBatch()->getChildren();
	CCObject* obj;
	
	CCARRAY_FOREACH(arrInvaders, obj)
	{
		InvaderBase* ib = (InvaderBase*)obj;
		
		if(ib->isActive())
		{
			InvaderType type = ib->getType();
			bool bOut;
			bOut = ib->updateInvader(dt);
			
			if(!bOut && (type == IT_Normal_3 || type == IT_Normal_4))
			{
				// 漏掉了一个
				mLifeCount--;
				Audio->playEffect(EF_MISS);
                
				// 漏掉时的效果
				CCPoint pos = ib->getPosition();
				if(pos.x > 460)
					pos.x = 460;
				else if(pos.x < 20)
					pos.x = 20;
				if(pos.y > 300)
					pos.y = 300;
				if(pos.y < 20)
					pos.y = 20;
				
                
				CCSprite* spriteMiss = HBcreateImageWithFrameName("x.png", pos.x, pos.y, this, false);
				spriteMiss->setScale(0);
				CCAction* action = CCSequence::create((CCFiniteTimeAction*)mActionMiss->copy()->autorelease(), CCCallFuncO::create(this, callfuncO_selector(LayerGame::_finishMiss), spriteMiss), NULL);
				spriteMiss->runAction(action);
				
				mLabelLifeCount->setString(fcs("x %d", mLifeCount));
				_blinkLife();
                
				if(mLifeCount <= 0)
					_endGame();
				break;
			}
			
			if(mDevourer->checkCollision(ib))
			{
				GDShared->curInvadersCount[type]++;
				
				if(type == IT_Bad && !mDevourer->isShieldOn())
				{
					Audio->playEffect(EF_MISS);
					_particleEF(0, ib->getPosition());
					ib->destroy();
					
					mLifeCount --;
					mLabelLifeCount->setString(fcs("x %d", mLifeCount));
					_blinkLife();
					
					if(mLifeCount <= 0)
						_endGame();
					break;
				}
                
				if(mDevourer->isShieldOn() && type == IT_Bad)
					Audio->playEffect(EF_COLSHIELD);
				else
				{
					switch(type)
					{
						case IT_Normal_1:
						case IT_Normal_2:
							Audio->playEffect(EF_COLNORMAL);
                            break;
						case IT_Normal_3:
						case IT_Normal_4:
							Audio->playEffect(EF_COLADVANCE);
							break;
						case IT_Bad:
							Audio->playEffect(EF_COLBAD);
							break;
						case IT_Gold:
						case IT_Gold2:
							GDShared->gold += ib->getScore();
							Audio->playEffect(EF_COLGOLD);
							break;
						default:
							break;
					}
                    
					int score = ib->getScore();
					if (score != 0)
					{
						GDShared->curScore += score;
						_scoreEF(ib->getPosition(), score, type);
					}
				}
                
				_particleEF(0, ib->getPosition());
				ib->destroy();
				break;
			}
		}
	} // FOR_EACH
}

void LayerGame::_explode(int type)
{
	CCObject* obj;
	CCArray* arrInv = mInvaders->getBatch()->getChildren();

	Audio->playEffect(EF_BOMB);
	
	_particleEF(1, mDevourer->getPosition());
	
	CCARRAY_FOREACH(arrInv, obj)
	{
		InvaderBase* ib = (InvaderBase*)obj;
		if(ib->isActive())
		{
			if(ib->getType() != IT_Bad)
				GDShared->curInvadersCount[ib->getType()]++;
			
			int score = abs(ib->getScore());
			if(score != 0)
			{
				GDShared->curScore += score;
				_scoreEF(ib->getPosition(), score, IT_Normal_1);
			}
			_particleEF(0, ib->getPosition());
			ib->destroy();
		}
	}
}

void LayerGame::_blinkLife()
{
	mLifes->runAction((CCAction*)mActionBlink->copy()->autorelease());
	mLabelLifeCount->runAction((CCAction*)mActionBlink->copy()->autorelease());
}

void LayerGame::_particleEF(int type, CCPoint pos)
{
    CCParticleSystemQuad* particle;
	if(type == 0)
		particle = CCParticleSystemQuad::create("particle_explode_small.plist");
	else
		particle = CCParticleSystemQuad::create("particle_explode_big.plist");
	particle->setAutoRemoveOnFinish(true);
	particle->setPosition(pos);
	addChild(particle, lzo_score);
}

void LayerGame::_scoreEF(CCPoint pos, int score, InvaderType type)
{
	mLayerExplodeScore->addChild(new ExplodeScore(pos, score, type));
}

void LayerGame::_updatePos()
{
	CCPoint pos = convertTouchToNodeSpace(mTouch);
	CCPoint devourerPos = mDevourer->getPosition();
	mDevourer->setDevourerPos(ccpAdd(devourerPos, ccpSub(pos, mLastTouchPos)));
	mLastTouchPos = pos;
}

void LayerGame::_endGame()
{
	mFinished = true;
	GDShared->curLastTime = mTimePassed;
	
	Audio->playEffect(EF_FINISH);
	
	// GAME OVER
	unschedule(schedule_selector(LayerGame::_levelup));
	unscheduleUpdate();

	mFinish->runAction(CCSequence::create(CCShow::create(), CCEaseBounceOut::create(CCMoveTo::create(0.3, HBgetPositionByPercent(50, 50))), CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(LayerGame::_callResult)), NULL));
}

void LayerGame::_callResult()
{
//k	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LayerResult::scene(), ccWHITE));
	Audio->playBackgroundMusic(MUSIC_BG1, true);
}

void LayerGame::_castSpell(Spell* spell)
{	
	if(spell->getType() == ST_Bomb)
	{
		_explode(1);
		return;
	}
	else
		Audio->playEffect(EF_CAST);

	_setState(spell);
	mBuff->addBuff(spell->getType());
}

void LayerGame::_setState(Spell* spell)
{
	switch(spell->getType())
	{
		case ST_Shield:
			_restoreShield();
			mDevourer->enableShield();
			mActionShield = CCSequence::create(CCDelayTime::create(spell->getDuration()), CCCallFunc::create(this, callfunc_selector(LayerGame::_restoreShield)), NULL);
			runAction(mActionShield);
			break;
		case ST_Freeze:
			_restoreFreeze();
			GDShared->curSpeedFactor = 0.5;
			mActionSpeed = CCSequence::create(CCDelayTime::create(spell->getDuration()), CCCallFunc::create(this, callfunc_selector(LayerGame::_restoreFreeze)), NULL);
			runAction(mActionSpeed);
			break;
		default:
			break;
	}
}

void LayerGame::_restoreShield()
{
	mDevourer->disableShield();
	if(mActionShield)
		stopAction(mActionShield);
	mActionShield = NULL;
}

void LayerGame::_restoreFreeze()
{
	GDShared->curSpeedFactor = 1;
	if(mActionSpeed)
		stopAction(mActionSpeed);
	mActionSpeed = NULL;
}

void LayerGame::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void LayerGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if(!mStarted || mFinished)
		return;
	
	CCTouch* touch;
	CCSetIterator itr;
	if(!mTouch)
	{
		// 判断按下
		for (itr = pTouches->begin(); itr != pTouches->end(); ++itr)
		{
			touch = (CCTouch*)*itr;
			CCPoint pos = convertTouchToNodeSpace(touch);
			mTouch = touch;
			mLastTouchPos = pos;
			break;
		}
	}
	
	// 判断魔法
	for (itr = pTouches->begin(); itr != pTouches->end(); ++itr)
	{
		touch = (CCTouch*)*itr;
		int index = mSpell->checkClick(touch);
		if(index >= 0)
		{
			Spell* spell = mSpell->getSpell(index);
			_castSpell(spell);
			spell->cast();
			break;
		}
	}
}

void LayerGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if(!mStarted || mFinished)
		return;

	if(mTouch && pTouches->containsObject(mTouch))
		_updatePos();
}

void LayerGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if(!mStarted || mFinished)
		return;
	
	if(mTouch && pTouches->containsObject(mTouch))
	{
		_updatePos();
		mTouch = NULL;
	}
}

void LayerGame::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	if(!mStarted || mFinished)
		return;

	if(mTouch && pTouches->containsObject(mTouch))
	{
		_updatePos();
		mTouch = NULL;
	}
}

void LayerGame::_finishMiss(CCObject* obj)
{
	CCSprite* sprite = (CCSprite*)obj;
	sprite->removeFromParentAndCleanup(true);
}