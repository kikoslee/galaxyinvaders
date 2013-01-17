#include "DlgReview.h"
#include "GlobalData.h"

DlgReview::DlgReview()
: mNodeBase(NULL)
, mLabelTitle(NULL)
, mLabelReviewMsg(NULL)
, mBtnReview(NULL)
, mBtnCancel(NULL)
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(tp_dialog);
}

DlgReview::~DlgReview()
{
    CC_SAFE_RELEASE(mNodeBase);
    CC_SAFE_RELEASE(mLabelReviewMsg);
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mBtnCancel);
    CC_SAFE_RELEASE(mBtnReview);
}

SEL_MenuHandler DlgReview::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgReview::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnCancel", DlgReview::onBtnCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnReview", DlgReview::onBtnReview);
    return NULL;
}

bool DlgReview::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeBase", CCNode*, mNodeBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelReviewMsg", CCLabelTTF*, mLabelReviewMsg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnCancel", CCControlButton*, mBtnCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnReview", CCControlButton*, mBtnReview);
    return false;
}

void DlgReview::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelTitle->setString(gls("Review"));
    mLabelReviewMsg->setString(gls("ReviewMsg"));
    mBtnCancel->setTitleForState(ccs(gls("Cancel")), CCControlStateNormal);
    mBtnReview->setTitleForState(ccs(gls("Review")), CCControlStateNormal);
    mBtnCancel->setDefaultTouchPriority(tp_dialogBtn);
    mBtnReview->setDefaultTouchPriority(tp_dialogBtn);
    
    Audio->playEffect(EF_POPBUY);
}

void DlgReview::onBtnCancel(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    getParent()->removeChild(this, true);
}

void DlgReview::onBtnReview(CCObject* pSender, CCControlEvent pCCControlEvent)
{
	Audio->playEffect(EF_CLICK);
    getParent()->removeChild(this, true);
    gotoReview();
}

bool DlgReview::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
