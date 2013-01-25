#include "DlgQuit.h"
#include "GlobalData.h"

DlgQuit::DlgQuit()
: mNodeBase(NULL)
, mLabelMsg(NULL)
, mBtnQuit(NULL)
, mBtnCancel(NULL)
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(tp_dialog);
}

DlgQuit::~DlgQuit()
{
    CC_SAFE_RELEASE(mNodeBase);
    CC_SAFE_RELEASE(mLabelMsg);
    CC_SAFE_RELEASE(mBtnCancel);
    CC_SAFE_RELEASE(mBtnQuit);
}

SEL_MenuHandler DlgQuit::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgQuit::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnCancel", DlgQuit::onBtnCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnQuit", DlgQuit::onBtnQuit);
    return NULL;
}

bool DlgQuit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeBase", CCNode*, mNodeBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMsg", CCLabelTTF*, mLabelMsg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnCancel", CCControlButton*, mBtnCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnQuit", CCControlButton*, mBtnQuit);
    return false;
}

void DlgQuit::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelMsg->setString(gls("QuitMsg"));
    mBtnCancel->setTitleForState(ccs(gls("Cancel")), CCControlStateNormal);
    mBtnQuit->setTitleForState(ccs(gls("Quit")), CCControlStateNormal);
    mBtnCancel->setDefaultTouchPriority(tp_dialogBtn);
    mBtnQuit->setDefaultTouchPriority(tp_dialogBtn);
    
    Audio->playEffect(EF_POPBUY);
}

void DlgQuit::onBtnCancel(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    getParent()->removeChild(this, true);
    gIsDlgQuitShow = false;
}

void DlgQuit::onBtnQuit(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBExitApplication();
}

bool DlgQuit::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
