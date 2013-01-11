#include "LayerStore.h"
#include "GlobalData.h"
#include "StoreItem.h"
#include "StoreItemLoader.h"
#include "LayerMainLoader.h"
#include "LayerGameLoader.h"
//#include "Dialog.h"
//#include "LayerBuy.h"
//#include "CommonHelper.h"
//#include "AdHelper.h"
//#include "LayerClip.h"
//#include "DataSL.h"
//#include "LayerHelp.h"

//SpellType sSpellIndex[3] = {ST_Bomb, ST_Freeze, ST_Shield};

LayerStore::LayerStore()
: mTitle(NULL)
, mTotalGold(NULL)
, mMultiplierTitle(NULL)
, mMultiplier(NULL)
, mNextObjTitle(NULL)
, mNextObjName(NULL)
, mNextObjDesc(NULL)
, mLayerTable(NULL)
, mBtnGo(NULL)
{
}

LayerStore::~LayerStore()
{
    CC_SAFE_RELEASE(mTitle);
    CC_SAFE_RELEASE(mTotalGold);
    CC_SAFE_RELEASE(mMultiplierTitle);
    CC_SAFE_RELEASE(mMultiplier);
    CC_SAFE_RELEASE(mNextObjTitle);
    CC_SAFE_RELEASE(mNextObjName);
    CC_SAFE_RELEASE(mNextObjDesc);
    CC_SAFE_RELEASE(mLayerTable);
    CC_SAFE_RELEASE(mBtnGo);
}

void LayerStore::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mTable = TableViewStore::create();
    mTable->createTable(mLayerTable->getContentSize());
    mLayerTable->addChild(mTable);

    update(0);
    scheduleUpdate();
}

SEL_MenuHandler LayerStore::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerStore::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBack", LayerStore::onBtnBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnGo", LayerStore::onBtnGo);
    return NULL;
}

bool LayerStore::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF*, mTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTotalGold", CCLabelTTF*, mTotalGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMultiplierTitle", CCLabelTTF*, mMultiplierTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMultiplier", CCLabelTTF*, mMultiplier);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNextObjTitle", CCLabelTTF*, mNextObjTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNextObjName", CCLabelTTF*, mNextObjName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNextObjDesc", CCLabelTTF*, mNextObjDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerTable", CCLayer*, mLayerTable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnGo", CCControlButton*, mBtnGo);
    return false;
}

void LayerStore::onBtnGo(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
//    if (gd->isFirstTime)
//    {
//        // 新手显示帮助
//        gd->isFirstTime = false;
//        gd->saveUserData();
//        LayerHelp* layer = LayerHelp::create();
//        getParent()->addChild(layer, 30000);
//    }
//    else
//    {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerGame", LayerGameLoader::loader())));
//        CCDirector::sharedDirector()->replaceScene(HBSceneLoader("LayerGame", LayerGameLoader::loader()));
//    }
}

void LayerStore::onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerMain", LayerMainLoader::loader())));
}

void LayerStore::update(float dt)
{
    mTotalGold->setString(fcs("%s", HBCommaPrint(GlobalData::shared()->gold)));
}

/*
void LayerStore::_menuCallback(CCObject* sender)
{
	switch(index)
	{
		case smtGo:
			break;
		case smtMoreGold:
            Audio->playEffect(EF_CLICK);
			_gotoLayerBuy();
			break;
	}
}

void LayerStore::_gotoLayerBuy()
{
	onExit();
//	LayerBuy* buy = LayerBuy::node();
//	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
//	scene->addChild(buy, 50000);
}

*/