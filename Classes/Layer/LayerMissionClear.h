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
private:
    CCSprite* mLight1;
    CCSprite* mLight2;
    CCAction* mAniLight;
    
    CCMenu* mMenu;
    
    void _aniLight1();
    void _aniLight2();
};
#endif
