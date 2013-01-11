#include "StoreItem.h"
#include "GlobalData.h"

#define StoreItemCount 7
static SpellType spellIndex[StoreItemCount] = {ST_Shield,ST_Freeze,ST_Bomb,ST_Bomb,ST_Shield,ST_Freeze,ST_Bomb};
static const char* name[StoreItemCount] = {"Shield Upgrade","Freeze Upgrade","Bomb Upgrade","Life","Shield","Freeze","Bomb"};
static const char* iconName[StoreItemCount] = {"spell_shield.png","spell_freeze.png","spell_bomb.png","icon_life.png","spell_shield.png","spell_freeze.png","spell_bomb.png",};
static const char* descStr[StoreItemCount] =
{
    "Reduce 'Shield' countdown time.",
    "Reduce 'Freeze' countdown time.",
    "Reduce 'Bomb' countdown time.",
    "Get 1 extra life permanently.",
    "Prevent from the destroy invader.",
    "Slow down the invaders' move speed.",
    "Destroy all invaders.",
};

StoreItem::StoreItem()
: mIcon(NULL)
, mName(NULL)
, mDesc(NULL)
, mCost(NULL)
, mSpector(NULL)
, mBtn(NULL)
{
    mStar[0] = mStar[1] = mStar[2] = 0;
}

StoreItem::~StoreItem()
{
    CC_SAFE_RELEASE(mIcon);
    CC_SAFE_RELEASE(mName);
    CC_SAFE_RELEASE(mDesc);
    CC_SAFE_RELEASE(mCost);
    CC_SAFE_RELEASE(mSpector);
    CC_SAFE_RELEASE(mBtn);
    CC_SAFE_RELEASE(mStar[0]);
    CC_SAFE_RELEASE(mStar[1]);
    CC_SAFE_RELEASE(mStar[2]);
}

void StoreItem::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{    
    mCount = HBcreateLabelAtlas("88", "fnt-number.png", 20, 26, '0', 10, 2, gAnchorRight, mIcon);
    mCount->setColor(gColorBtn);
}

SEL_MenuHandler StoreItem::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler StoreItem::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClicked", StoreItem::onBtnClicked);
    return NULL;
}

bool StoreItem::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIcon", CCSprite*, mIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStar1", CCSprite*, mStar[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStar2", CCSprite*, mStar[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStar3", CCSprite*, mStar[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSpector", CCScale9Sprite*, mSpector);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF*, mName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDesc", CCLabelTTF*, mDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCost", CCLabelTTF*, mCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtn", CCControlButton*, mBtn);
    return false;
}

void StoreItem::onBtnClicked(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    SpellType type = spellIndex[mIndex];
    if (mIndex > 3)
    {
        // 装配
        int cost = GDShared->getSpell(type).equipCost;
        
        if (GDShared->gold >= cost)
        {
            Audio->playEffect(EF_EQUIPSPELL);
            GDShared->gold -= cost;
            GDShared->spellCount[type]++;
            GDShared->saveUserData();
            updateItem(mIndex);
        }
        else
        {
//            _gotoLayerBuy();
        }
    }
    else if (mIndex == 3)
    {
        // 加生命
        int level = GDShared->maxLife;
        int cost = level * 10000;
        if (GDShared->gold >= cost)
        {
            Audio->playEffect(EF_UPSPELL);
            GDShared->gold -= cost;
            GDShared->maxLife++;
            GDShared->saveUserData();
            updateItem(mIndex);
        }
        else
        {
//            _gotoLayerBuy();   
        }
    }
    else
    {
        int spellLevel = GDShared->spellLevel[type];
        int cost = GDShared->getSpell(type).upgradeCost[spellLevel];
        
        if (GDShared->gold >= cost)
        {
            Audio->playEffect(EF_UPSPELL);
            GDShared->spellLevel[type]++;
            GDShared->gold -= cost;
            GDShared->saveUserData();
            updateItem(mIndex);
        }
        else
        {
//            _gotoLayerBuy();
        }
    }
}

void StoreItem::updateItem(int index)
{
    mIndex = index;
    
    SpellType type = spellIndex[index];
    const SpellData& sd = GDShared->getSpell(type);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    mName->setString(gls(name[index]));
    mIcon->setDisplayFrame(cache->spriteFrameByName(iconName[index]));
    
    // 当前数量
    if (index > 3)
    {
        mCount->setVisible(true);
        mCount->setString(fcs("%d", GDShared->getSpellCount(type)));
        mCost->setString(fcs(":%d", sd.equipCost));
    }
    else if (index == 3)
    {
        mCount->setVisible(true);
        mCount->setString(fcs("%d", GDShared->maxLife));
        mCost->setString(fcs(":%d", GDShared->maxLife * 10000));
    }
    else
    {
        mCount->setVisible(false);
        int spellLevel = GDShared->getSpellLevel(type);
        for (int j = 0; j < 3; j++)
        {
            if (j < spellLevel)
                mStar[j]->setDisplayFrame(cache->spriteFrameByName("icon_star.png"));
            else
                mStar[j]->setDisplayFrame(cache->spriteFrameByName("icon_star_d.png"));
        }
        
        int cdTime = (int)(sd.cdTime[spellLevel]);
        
        if (spellLevel >= 3)
        {
            mDesc->setString(fcs("%s\n%s:%d (%s)", gls(descStr[index]), gls("Current"), cdTime, gls("MAX")));
            mCost->setString(fcs(":%s", gls("MAX")));
        }
        else
        {
            int nextCDTime = (int)(sd.cdTime[spellLevel+1]);
            mDesc->setString(fcs("%s\n%s:%d -> %s:%d", gls(descStr[index]), gls("Current"), cdTime, gls("Next"), nextCDTime));
            mCost->setString(fcs(":%d", sd.upgradeCost[spellLevel]));
        }
    }
    
    if (index == StoreItemCount - 1)
        mSpector->setVisible(false);
    else
        mSpector->setVisible(true);

}