#ifndef _LayerResult_H_
#define _LayerResult_H_

#include "HBCommon.h"

class LayerResult
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    LayerResult();
    virtual ~LayerResult();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerResult, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    //
    //    void onMenuTestClicked(CCObject* pSender, CCControlEvent pCCControlEvent);
    
private:
	bool mMissionClear;		// 当前任务是否达成
	CCLabelTTF* mLabelMulti;
    CCLabelTTF* mLabelGold;
    
    CCLabelTTF* mLabelInvaderCount[4];
    CCLabelTTF* mLabelScore;
    CCLabelTTF* mLabelLastTime;
    
    CCLabelTTF* mGoalName;
    CCLabelTTF* mGoalDesc;
    
    float mCurTime;
    int mCurStep;
    
	void _menuCallback(CCObject* sender);
	void _createLayer();
	void _checkMission();
	void _dialogReturn();
    void _refreshView();
	
    void _showMissionClear();
	void _clearShowFinish();		// Clear标签出现动画完成
	void _addMultiFinish(CCObject* object);
    
public:
//	bool init();  
		
//    void update(float dt);
//	bool ccTouchBegan(CCTouch* touch, CCEvent *event);
};

#endif