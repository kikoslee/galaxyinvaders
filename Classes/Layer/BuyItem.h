#ifndef _BuyItem_H_
#define _BuyItem_H_

#include "HBCommon.h"

class LayerBuy;
class BuyItem
: public CCNode
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    BuyItem();
    virtual ~BuyItem();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyItem, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    void setIndex(LayerBuy* parent, int index);

private:
    LayerBuy* mParent;
    int mIndex;
    
    CCLabelTTF* mLabelGold;
    CCLabelTTF* mLabelMoney;
    CCSprite* mIcon;
    CCSprite* mIconSave;
    CCControlButton* mBtnBuy;

    void onBtnBuy(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif