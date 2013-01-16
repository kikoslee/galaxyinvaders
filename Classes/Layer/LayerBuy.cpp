#include "LayerBuy.h"
#include "GlobalData.h"

LayerBuy::LayerBuy()
: mLabelTitle(NULL)
, mBtnClose(NULL)
, mLayerBase(NULL)
, mLayerMask(NULL)
, mLabelPurchase(NULL)
{
    for (int i = 0; i < 6; i++)
        mBuyItem[i] = NULL;

    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(tp_dialog);
}

LayerBuy::~LayerBuy()
{
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mBtnClose);
    for (int i = 0; i < 6; i++)
        CC_SAFE_RELEASE(mBuyItem[i]);
    CC_SAFE_RELEASE(mLayerMask);
    CC_SAFE_RELEASE(mLabelPurchase);
    CC_SAFE_RELEASE(mLayerBase);
}

SEL_MenuHandler LayerBuy::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerBuy::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClose", LayerBuy::onBtnClose);
    return NULL;
}

bool LayerBuy::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerBase", CCLayerColor*, mLayerBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem0", BuyItem*, mBuyItem[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem1", BuyItem*, mBuyItem[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem2", BuyItem*, mBuyItem[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem3", BuyItem*, mBuyItem[3]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem4", BuyItem*, mBuyItem[4]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBuyItem5", BuyItem*, mBuyItem[5]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnClose", CCControlButton*, mBtnClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerMask", CCLayerColor*, mLayerMask);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelPurchase", CCLabelTTF*, mLabelPurchase);
    
    return false;
}

void LayerBuy::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelTitle->setString(gls("More Coin"));
    mBtnClose->setTitleForState(ccs(gls("Close")), CCControlStateNormal);
    mBtnClose->setDefaultTouchPriority(tp_dialogBtn);
    
    mLabelPurchase->setString(gls("Purchasing..."));
    mLayerMask->setTouchPriority(tp_dialogBtn - 1);
    mLayerMask->setVisible(false);
    
    for (int i = 0; i < 6; i++)
        mBuyItem[i]->setIndex(this, i);
    
    // 出现动画
	mLayerBase->setPosition(HBgetPositionByPercent(100, 0));
	mLayerBase->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5, CCPointZero)));
	Audio->playEffect(EF_POPBUY);
}

void LayerBuy::onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    mLayerBase->runAction(CCSequence::create(CCScaleTo::create(0.2, 0), CCCallFunc::create(this, callfunc_selector(LayerBuy::_destroyLayer)), NULL));
}

void LayerBuy::_destroyLayer()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	CCArray* layers = scene->getChildren();

	CCObject* child = NULL;
	CCARRAY_FOREACH(layers, child)
	{
		CC_BREAK_IF(!child);
		CCLayer* layer =(CCLayer*)child;
		if(!layer->isRunning())
			layer->onEnter();
	}
	scene->removeChild(this, true);
//	getParent()->removeChild(this, true);
}

bool LayerBuy::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void LayerBuy::purchaseStart(int index)
{
    mLayerMask->setVisible(true);
    HBPurchase::shared()->purchaseItem(index, this, callfuncO_selector(LayerBuy::purchaseSuccess), callfuncO_selector(LayerBuy::purchaseFailed));
}

void LayerBuy::purchaseSuccess(CCString* itemName)
{
    mLayerMask->setVisible(false);
    GDShared->addPurchaseGold(itemName->getCString());
}

void LayerBuy::purchaseFailed(CCString* itemName)
{
    mLayerMask->setVisible(false);
}
