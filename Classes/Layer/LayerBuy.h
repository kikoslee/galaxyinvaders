#ifndef _LayerBuy_H_
#define _LayerBuy_H_

#include "HBCommon.h"
#include "BuyItem.h"

class LayerBuy
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    LayerBuy();
    virtual ~LayerBuy();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerBuy, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

    void onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    void purchaseStart(int index);
    void purchaseSuccess(CCString* itemName);
    void purchaseFailed(CCString* itemName);
    
private:
    CCLabelTTF* mLabelTitle;
    BuyItem* mBuyItem[6];
    CCControlButton* mBtnClose;
    CCLayerColor* mLayerBase;
    CCLayerColor* mLayerMask;
    CCLabelTTF* mLabelPurchase;
    
	// 销毁层
	void _destroyLayer();
};

#endif