#ifndef _LayerPause_H_
#define _LayerPause_H_

#include "HBCommon.h"

class LayerPause
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    LayerPause();
    virtual ~LayerPause();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerPause, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

private:
    CCLabelTTF* mLabelCurrentMission;
    CCLabelTTF* mLabelMissionName;
    CCLabelTTF* mLabelMissionDesc;
    CCLabelTTF* mLabelAllInvaders;
    CCLabelTTF* mLabelCount[5];
    
    CCControlButton* mBtnSound;
    CCControlButton* mBtnExit;
    CCControlButton* mBtnContinue;

    void onBtnSound(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnHelp(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnExit(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnContinue(CCObject* pSender, CCControlEvent pCCControlEvent);
    
    void _refreshSoundBtn();
};

#endif