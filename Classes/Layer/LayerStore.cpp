#include "LayerStore.h"
#include "GlobalData.h"
#include "StoreItem.h"
#include "StoreItemLoader.h"
#include "LayerMainLoader.h"
#include "LayerGameLoader.h"
#include "LayerHelpLoader.h"

LayerStore::LayerStore()
: mLabelTitle(NULL)
, mLayerTable(NULL)
, mBtnGo(NULL)
{
}

LayerStore::~LayerStore()
{
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mLayerTable);
    CC_SAFE_RELEASE(mBtnGo);
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerTable", CCLayer*, mLayerTable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnGo", CCControlButton*, mBtnGo);
    return false;
}

void LayerStore::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mTable = TableViewStore::create();
    mTable->createTable(mLayerTable->getContentSize());
    mLayerTable->addChild(mTable);
    
    mLabelTitle->setString(gls("Equip Skill"));
    mBtnGo->setTitleForState(ccs(gls("GO")), CCControlStateNormal);
}

void LayerStore::onBtnGo(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBUmeng::event("Button", "StoreGo");
	Audio->playEffect(EF_CLICK);
    if (GDShared->isFirstTime)
    {
        // 新手显示帮助
        GDShared->isFirstTime = false;
        GDShared->saveUserData();
        LayerHelp* layer = (LayerHelp*)HBLayerLoader("LayerHelp", LayerHelpLoader::loader());
        getParent()->addChild(layer, 30000);
    }
    else
    {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerGame", LayerGameLoader::loader())));
    }
}

void LayerStore::onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerMain", LayerMainLoader::loader())));
}
