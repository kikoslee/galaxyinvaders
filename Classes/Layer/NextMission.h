#ifndef _NextMission_H_
#define _NextMission_H_

#include "HBCommon.h"

class NextMission
: public CCLayer
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    NextMission();
    virtual ~NextMission();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(NextMission, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

private:
    CCLabelTTF* mLabelNextTitle;
    CCLabelTTF* mLabelMissionName;
    CCLabelTTF* mLabelMissionDesc;
    CCLabelTTF* mLabelMultiTitle;
    CCLabelTTF* mLabelMultiplier;
};

#endif