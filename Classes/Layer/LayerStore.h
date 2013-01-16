#ifndef _LayerStore_H_
#define _LayerStore_H_

#include "HBCommon.h"
//#include "SpellSlot.h"
#include "TableViewStore.h"

class LayerStore
    : public CCLayer
    , public CCBSelectorResolver
    , public CCBMemberVariableAssigner
    , public CCNodeLoaderListener
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerStore, create);
    
    LayerStore();
    virtual ~LayerStore();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

    void onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnGo(CCObject* pSender, CCControlEvent pCCControlEvent);
    
private:
    CCLabelTTF* mLabelTitle;
    CCLayer* mLayerTable;
    CCControlButton* mBtnGo;
    
    TableViewStore* mTable;
};

#endif