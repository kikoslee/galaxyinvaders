#ifndef _DlgQuit_H_
#define _DlgQuit_H_

#include "HBCommon.h"

class DlgQuit
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    DlgQuit();
    virtual ~DlgQuit();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DlgQuit, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    void onBtnQuit(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnCancel(CCObject* pSender, CCControlEvent pCCControlEvent);

private:
    CCNode* mNodeBase;
    CCLabelTTF* mLabelMsg;
    CCControlButton* mBtnQuit;
    CCControlButton* mBtnCancel;
};
#endif
