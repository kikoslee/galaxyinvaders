#ifndef _StoreItem_H_
#define _StoreItem_H_

#include "HBCommon.h"

class StoreItem
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StoreItem, create);
    
    StoreItem();
    virtual ~StoreItem();
    
    static CCScene* createItem();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    void updateItem(int index);

private:
    CCSprite* mIcon;
    CCLabelTTF* mName;
    CCLabelTTF* mDesc;
    CCLabelTTF* mCost;
    CCSprite* mStar[3];
    CCScale9Sprite* mSpector;
    
    CCControlButton* mBtn;
    
    CCLabelAtlas* mCount;
    
    int mIndex;
    
    void onBtnClicked(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif