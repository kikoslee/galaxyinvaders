#ifndef _LayerMain_H_
#define _LayerMain_H_

#include "HBCommon.h"

class LayerMain
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerMain, create);
    
    LayerMain();
    virtual ~LayerMain();
    
    static CCScene* createScene();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
private:
    CCLabelTTF* mLabelTitle;
    CCLabelTTF* mLabelCurObjName;
    CCLabelTTF* mLabelCurObjDesc;
    
    CCControlButton* mBtnSound;
    
    void _refreshSoundBtn();
    
    void onBtnSound(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnPlay(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnRank(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnMore(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif