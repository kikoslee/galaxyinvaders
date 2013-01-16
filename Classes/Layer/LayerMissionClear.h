#ifndef _LayerMissionClear_H_
#define _LayerMissionClear_H_

#include "HBCommon.h"

class LayerMissionClear
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    LayerMissionClear();
    virtual ~LayerMissionClear();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerMissionClear, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    void onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent);

private:
    CCSprite* mLight1;
    CCSprite* mLight2;
    
    CCLabelTTF* mLabelCurObjName;
    CCLabelTTF* mLabelCurObjDesc;
    CCLabelTTF* mLabelGold;
    CCLabelTTF* mLabelMultiTitle;
    CCLabelTTF* mLabelMulti;
    CCLabelTTF* mLabelNextObjName;
    CCLabelTTF* mLabelNextObjDesc;
    
    CCControlButton* mBtnClose;
    
    CCAction* mAniLight;

    void _aniLight1();
    void _aniLight2();
};
#endif
