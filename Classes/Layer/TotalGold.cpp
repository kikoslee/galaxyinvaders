#include "TotalGold.h"
//#include "LayerGame.h"
#include "LayerStoreLoader.h"
//#include "LayerHelp.h"
#include "GlobalData.h"

TotalGold::TotalGold()
: mLabelGold(NULL)
, mBtnGold(NULL)
{
}

TotalGold::~TotalGold()
{
    CC_SAFE_RELEASE(mLabelGold);
    CC_SAFE_RELEASE(mBtnGold);
}

SEL_MenuHandler TotalGold::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler TotalGold::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnGold", TotalGold::onBtnGold);
    return NULL;
}

bool TotalGold::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGold", CCLabelTTF*, mLabelGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnGold", CCControlButton*, mBtnGold);
    return false;
}

void TotalGold::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold).c_str()));
    scheduleUpdate();
}

void TotalGold::onBtnGold(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBUmeng::event("Button", "TotalGold");
	Audio->playEffect(EF_CLICK);
    GDShared->showLayerBuy();
}

void TotalGold::update(float dt)
{
    mLabelGold->setString(fcs("%s", HBCommaPrint(GDShared->gold).c_str()));
}

void TotalGold::enableBtn(bool enable)
{
    mBtnGold->setEnabled(enable);
}