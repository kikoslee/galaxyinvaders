#ifndef _LayerGame_H_
#define _LayerGame_H_

#include "ChanceDecision.h"
#include "Devourer.h"
#include "InvaderManager.h"
#include "SpellSlot.h"
#include "BuffManager.h"

#include "HBCommon.h"

class LayerGame
    : public CCLayer
    , public CCBSelectorResolver
    , public CCBMemberVariableAssigner
    , public CCNodeLoaderListener
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerGame, create);
    
    LayerGame();
    virtual ~LayerGame();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    void onBtnPause(CCObject* pSender, CCControlEvent pCCControlEvent);
    
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();

	virtual void update(float dt);
    
private:
	CCLayer* mLayerExplodeScore;
	Devourer* mDevourer;
	InvaderManager* mInvaders;
	SpellSlot* mSpell;
	BuffManager* mBuff;
	ChanceDecision mChance;

	int mLevel;
	int mSubLevel;

    CCLayer* mLayerGame;
    CCSprite* mReady;
    CCSprite* mGo;
    CCSprite* mFinish;
	CCLabelTTF* mLabelScore;			// 分数
	CCLabelTTF* mLabelTime;				// 经过时间
	CCLabelTTF* mLabelGold;

	CCSprite* mLifes;					// 命的图标
	CCLabelTTF* mLabelLifeCount;		// 命数
	int mLifeCount;						// 剩余命数

	CCAction* mActionBlink;				// 丢命时闪烁动画
	CCAction* mActionSpeed;				// 减速动画
	CCAction* mActionShield;			// 护盾动画
	CCAction* mActionMiss;				// XX动画

	float mEmitRate;					// 侵略者发射间隔
	float mEmitTime;					// 当前发射时间记录
	float mTimePassed;

	CCTouch* mTouch;
	CCPoint mLastTouchPos;
	
	bool mStarted;
	bool mFinished;

	void _levelup(float dt);
	void _updateInvader(float dt);

	void _startGame();
	void _endGame();
	void _callResult();

	void _particleEF(int type, CCPoint pos);
	void _scoreEF(CCPoint pos, int score, InvaderType type);
	void _explode(int type);

	void _castSpell(Spell* spell);
	void _setState(Spell* spell);
	void _restoreFreeze();
	void _restoreShield();

	void _blinkLife();				// 丢命时闪烁
	void _updatePos();

	void _finishMiss(CCObject* obj);
//
//public:
//    void onEnter();
//	
};

#endif