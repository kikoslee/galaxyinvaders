#ifndef _TotalGold_H_
#define _TotalGold_H_

#include "HBCommon.h"

class TotalGold
: public CCNode
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    TotalGold();
    virtual ~TotalGold();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TotalGold, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    virtual void update(float dt);
    
    void enableBtn(bool enable);

private:
    CCLabelTTF* mLabelGold;
    CCControlButton* mBtnGold;

    void onBtnGold(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif