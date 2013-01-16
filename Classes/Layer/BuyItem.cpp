#include "BuyItem.h"
//#include "LayerGame.h"
//#include "LayerStoreLoader.h"
//#include "LayerHelp.h"
#include "GlobalData.h"
#include "LayerBuy.h"

BuyItem::BuyItem()
: mLabelGold(NULL)
, mLabelMoney(NULL)
, mIcon(NULL)
, mIconSave(NULL)
, mBtnBuy(NULL)
, mIndex(-1)
, mParent(NULL)
{
}

BuyItem::~BuyItem()
{
    CC_SAFE_RELEASE(mLabelGold);
    CC_SAFE_RELEASE(mLabelMoney);
    CC_SAFE_RELEASE(mIcon);
    CC_SAFE_RELEASE(mIconSave);
    CC_SAFE_RELEASE(mBtnBuy);
}

SEL_MenuHandler BuyItem::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler BuyItem::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBuy", BuyItem::onBtnBuy);
    return NULL;
}

bool BuyItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGold", CCLabelTTF*, mLabelGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMoney", CCLabelTTF*, mLabelMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIcon", CCSprite*, mIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIconSave", CCSprite*, mIconSave);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnBuy", CCControlButton*, mBtnBuy);
    return false;
}

void BuyItem::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mBtnBuy->setTitleForState(ccs(gls("Buy")), CCControlStateNormal);
    mBtnBuy->setDefaultTouchPriority(tp_dialogBtn);
}

void BuyItem::onBtnBuy(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    assert(mIndex >= 0);
    mParent->purchaseStart(mIndex);
}

void BuyItem::setIndex(LayerBuy* parent, int index)
{
    mParent = parent;
    mIndex = index;
    assert(mIndex >= 0);

    mLabelGold->setString(fcs("%d", gIapGold[mIndex]));
    string fee = HBPurchase::shared()->getItemCost(mIndex);
    if (fee.length() > 0)
        mLabelMoney->setString(fcs(" = %s", fee.c_str()));
    else
        mLabelMoney->setString(fcs(" = %s", GDShared->mDefaultPurchaseFee[mIndex].c_str()));
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    mIcon->setDisplayFrame(cache->spriteFrameByName(fcs("icon_buy%d.png", mIndex+1)));
    
    if (mIndex > 2)
    {
        mIconSave->setVisible(true);
        mIconSave->setDisplayFrame(cache->spriteFrameByName(fcs("icon_save%d.png", mIndex-2)));
    }
}
