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

    void onBtnContinue(CCObject* pSender, CCControlEvent pCCControlEvent);
    
    virtual void update(float dt);
    
private:
	bool mMissionClear;		// 当前任务是否达成

    CCLabelTTF* mLabelGold;
    CCLabelTTF* mLabelCount[4];
    CCLabelTTF* mLabelScore;
    CCLabelTTF* mLabelLastTime;
    CCLabelTTF* mLabelTitle;
    
    CCControlButton* mBtnContinue;
    
    float mCurTime;
    int mCurStep;
    
	void _menuCallback(CCObject* sender);
	void _checkMission();
	void _dialogReturn();
	
    void _showMissionClear();
	void _clearShowFinish();		// Clear标签出现动画完成
	void _addMultiFinish(CCObject* object);
};

#endif