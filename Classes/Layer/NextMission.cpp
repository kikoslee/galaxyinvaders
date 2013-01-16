#include "NextMission.h"
#include "GlobalData.h"

NextMission::NextMission()
: mLabelNextTitle(NULL)
, mLabelMissionName(NULL)
, mLabelMissionDesc(NULL)
, mLabelMultiTitle(NULL)
, mLabelMultiplier(NULL)
{
}

NextMission::~NextMission()
{
    CC_SAFE_RELEASE(mLabelNextTitle);
    CC_SAFE_RELEASE(mLabelMissionName);
    CC_SAFE_RELEASE(mLabelMissionDesc);
    CC_SAFE_RELEASE(mLabelMultiTitle);
    CC_SAFE_RELEASE(mLabelMultiplier);
}

bool NextMission::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelNextTitle", CCLabelTTF*, mLabelNextTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMissionName", CCLabelTTF*, mLabelMissionName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMissionDesc", CCLabelTTF*, mLabelMissionDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMultiTitle", CCLabelTTF*, mLabelMultiTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMultiplier", CCLabelTTF*, mLabelMultiplier);
    return false;
}

void NextMission::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelNextTitle->setString(gls("Next Mission"));
    mLabelMissionName->setString(GDShared->getCurObjName());
    mLabelMissionDesc->setString(GDShared->getCurObjDesc());
    mLabelMultiTitle->setString(gls("Multiplier"));
    mLabelMultiplier->setString(fcs("x%d", GDShared->multiplier));
}
